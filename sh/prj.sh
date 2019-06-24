function err() {
    echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&2
    return 1
}

function msg() {
    echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&1
    return 0
}

# Print base64(md5(random 16 bytes))
function random_content_md5_header_value() {
    dd if=/dev/urandom of=/dev/stdout bs=1 count=16 2>/dev/null | openssl dgst -md5 -binary | openssl enc -base64
}

# Print HTTP content_md5 header value for given file($1)
function content_md5_header_value() {
    local file=$1
    if [ ! -f "${file:?}" ] ; then
       err "${file} not exist"
       return 1
    fi

    cat $file | openssl dgst -md5 -binary | openssl enc -base64
}

PRJ_WORKSPACE_DIR="$HOME/workspace/Project"

# List all patches under dir=$1
function  prj_ls_patches() {
    local dir=$1
    find ${dir:="$PRJ_WORKSPACE_DIR/patches"} -type f -iname "*.patch"
}

# List all firmwares under dir=$1 sorted by mtime
function prj_ls_patches_by_mtime() {
    local dir=$1
    find ${dir:="$PRJ_WORKSPACE_DIR/patches"} -type f -iname "*.patch" -printf "%T@ %Tc %p\n" | sort -n | awk '{ print $9; }'
}

# Print latest patch path
function prj_latest_patch() {
    prj_ls_patches_by_mtime | tail -n 1
}

function prj_apply_patch() {
    local patch="$1"
    cd "$PRJ_WORKSPACE_DIR/git/repo"
    patch -p0 < ${patch:?}
    cd -
}

# List all firmwares under dir=$1
function  prj_ls_firmwares() {
    local dir=$1
    find ${dir:="$PRJ_WORKSPACE_DIR/firmwares"} -type f -iname "firmware*.tgz"
}

# List all firmwares under dir=$1 sorted by mtime
function prj_ls_firmwares_by_mtime() {
    local dir=$1
    find ${dir:="$PRJ_WORKSPACE_DIR/firmwares"} -type f -iname "firmware*.tgz" -printf "%T@ %Tc %p\n" | sort -n | awk '{ print $7; }'
}

# Print latest firmware path
function prj_latest_firmware() {
    prj_ls_firmwares_by_mtime | tail -n 1
}

# Select firmware via GUI
# $1 - dir to search for firmwares
function prj_ls_firmwares_gui() {
    local dir=$1
    local firmwares=$(prj_ls_firmwares ${dir:="$PRJ_WORKSPACE_DIR/firmwares"})
    local firmware=$(zenity --list --width=900 --height=300 --title "Choose firmware" --column "Firmware" $firmwares)
    echo ${firmware:?}
}

# Upload firmware($1) to appliance($2)
# $1 - path to firmware file
# $2 - appliance ip or hostname
# returns uploaded firmware name at appliance
function prj_upload_firmware() {
    local firmware=$1
    local appliance=$2
    local res=$(curl  --write-out %{http_code} --silent --output /dev/null \
		      -X PUT --data-binary @"${firmware:?}" \
		      -H 'Content-Type: application/octet-stream' "http://${appliance:?}/app/createUpdateFile/name=project-$USER-$RANDOM.tgz")
    if [ ! "${res:?}" -eq "200" ]
    then
        return err "firmware uploading FAILED. curl response: $res"
    fi

    echo "project-$USER-$RANDOM.tgz"
}

# Upgrade firmware($1) at appliance($2)
# $1 - name of firmware at appliance
# $2 - appliance ip
function prj_upgrade_firmware {
    local firmware=$1
    local appliance=$2
    local res=$(curl  --write-out %{http_code} --silent --output /dev/null \
		      -X PUT -H 'Content-Type: application/octet-stream' "http://${appliance:?}/app/runUpdate/name=${firmware?:}")
    if [ ! "${res:?}" -eq "200" ]
    then
        return $(err "upgrade procedure FAILED. curl response: $res")
    fi
}

# Upload firmware($1) to appliance($2) and upgrade
# $1 - path to firmware file
# $2 - appliance ip
function prj_upload_upgrade_firmware() {
    local firmware=$1
    local appliance=$2
    local name=$(prj_upload_firmware ${firmware:?} ${appliance:?})
    return $(prj_upgrade_firmware ${name:?} $appliance)
}

#
# Build function
#

# rsync local project sources to remote appliance
# $1 - local project dir path
# $2 - remote project dir absolute path
# $3 - remote user name
# $4 - appliance ip
# example: prj_sync_repo . /root/Company/Project root 192.168.10.32
function prj_sync_repo() {
    local local_dir=$1
    local remote_dir=$2
    local remote_user=$3
    local appliance=$4

    ssh ${remote_user:?}@${appliance:?} "
if [ ! -d \"${remote_dir:?}\" ]; then
   mkdir -p $remote_dir && echo \"Directory $remote_dir is created at appliance(${appliance:?})\"
fi
"
    rsync -rctvzL --stats		\
          --exclude .sconsign.dblite	\
          --exclude .svn		\
          --exclude .git		\
          --exclude .dir-locals.el	\
          --exclude .projectile		\
          --exclude .sconsign.dblite	\
          --exclude GPATH		\
          --exclude GRTAGS		\
          --exclude GTAGS		\
          --exclude Makefile		\
          --exclude build		\
          --exclude build.sh		\
          --exclude build_info		\
          --exclude build_ver.h		\
          --exclude output.map		\
          --exclude upgrade_firmware.sh \
          --delete ${local_dir:?} $remote_user@${appliance}:$remote_dir

    return 0
}

# Download last builded firmware from appliace
# $1 - local dir to store firmware
# $2 - remote project dir absolute path
# $3 - remote user name
# $4 - appliance ip
# $5 - firmware label name
# example: prj_get_firmware . /root/Company/Project root 192.168.10.32 label_example
function prj_get_firmware() {
    local local_dir=$1
    local remote_dir=$2
    local remote_user=$3
    local appliance=$4
    local label=$5

    local res=$(ssh ${remote_user:?}@${appliance:?} "
if [ ! -f \"${remote_dir:?}/firmware.tgz\" ]; then
   echo \"$remote_dir/firmware.tgz is missing at appliance($appliance)\"
else
   echo \"exist\"
fi
")

    if [ "$res" != "exist" ] ; then
    	return $(err "$RES")
    fi

    # download
    rsync -rctvz $remote_user@${appliance}:$remote_dir/firmware.tgz ${local_dir:?}

    # rename
    mv $local_dir/firmware.tgz $local_dir/firmware-${label:?}.tgz
    mv $local_dir/firmware-$label.tgz "$PRJ_WORKSPACE_DIR/firmwares/firmware-$label.tgz"

    return 0
}

# Start build process
# $1 - remote project dir absolute path
# $2 - remote user name
# $3 - appliance ip
# $4 - parallel jobs count
# $5 - build params
# $6 - build label
# example: prj_run_build /root/Company/Project root 192.168.10.32 12 debug=1 label_example
function prj_run_build() {
    local remote_dir=$1
    local remote_user=$2
    local appliance=$3
    local jobs=$4
    local build_params=$5
    local label=$6

    ssh ${remote_user:?}@${appliance:?} "
export PATH=\"/usr/lib/ccache/:$PATH\"
export CC='ccache gcc'
export CXX='ccache g++'
export label=${label:?}
echo label=${label}
cd ${remote_dir:?}
scons -j $JOBS ${build_params:?}
sh package.sh
ccache --show-stats
"
    # use '--debug=presub' option for debugging scons
    # return exit code somehow
}

# Generate firmware build label and patch
# $1 - local dir with git repo
# $2 - build params
# example: prj_build_label . debug=1
function prj_build_label() {
    local local_dir=$1
    local build_params=$2

    local temp_file=$(mktemp /tmp/prj.XXXXXX)
    local label=''

    if [ -d "$local_dir/../.git" ]; then
	local commit_hash=$(cd $local_dir && git rev-parse --verify --short HEAD 2>/dev/null)
	local branch=$(cd $local_dir && git symbolic-ref --short -q HEAD 2>/dev/null)
	git diff --no-prefix "$local_dir" > "$temp_file"
	label=${branch}-${commit_hash}
    fi

    if [ -z "$label" ]; then
	return err "Not a svn or git repo"
    fi

    if [[ $build_params == *"release=1"* ]]; then
	label=${label}-release
    fi

    if [[ $build_params == *"debug=1"* ]]; then
	label=${label}-debug
    fi

    if [[ $build_params == *"debug-3party=1"* ]]; then
	label=${label}-debug-3party
    fi

    if [[ $build_params == *"memtrace=1"* ]]; then
	label=${label}-memtrace
    fi

    if [[ $build_params == *"membb=1"* ]]; then
	label=${label}-membb
    fi

    if [[ $build_params == *"64bit=1"* ]]; then
	label=${label}-64bit
    fi

    local diff_lines=$(awk 'END { print NR; }' "$temp_file")
    if [ "$diff_lines" -eq "0" ]; then
	label=${label}-clean
    else
	local sha1=$(sha1sum "$temp_file" | awk '{ print $1; }')
	$(mv -T "$temp_file" "$PRJ_WORKSPACE_DIR/patches/${label}-diff-${sha1}.patch")
	label=${label}-diff-${sha1}
    fi

    echo "$label"
    return 0
}

DEBEMAIL="sergey.pashaev@gmail.com"
DEBFULLNAME="Sergey Pashaev"
export DEBEMAIL DEBFULLNAME

read -d '' PRJ_APPLIANCES_IP <<EOF
192.168.10.32
192.168.10.33
192.168.1.12
172.17.1.91
172.17.1.60
172.17.3.121
EOF

read -d '' PRJ_APPLIANCES <<EOF
ops-appliance-vm
ops-appliance-vm2
ops-appliance-12
prj-appliance-91
prj-appliance-60
prj-appliance-3-121
EOF

function prj_appliance_config() {
    local appliance=$(echo "${PRJ_APPLIANCES_IP}" | fzf)
    sshpass -p 'config' ssh config@${appliance:?}
}

# List result dirs for test=$1
function prj_ls_results() {
    local testdir="$1"
    find "${testdir:?}Results" -type d -printf "%T+\t%p\n" | sort -n | cut -f 2
}

function prj_latest_result() {
    local testdir="$1"
    prj_ls_results "${testdir:?}" | tail -n 1
}

function prj_latest_result_logs {
    local testdir="$1"
    local path="$(prj_latest_result "${testdir:?}")"
    cd "${path:?}"
    tail -n +1 *.log
    cd -
}

function prj_addr2line {
    local logfile="$1"
    local binary="$2"

    grep -E 'abort at| Fault at' "${logfile:?}"| cut -c 36- | uniq | cut -d : -f 2 | while read -r line ; do
	echo "ADDR:$line"
	addr2line -e "${binary:?}" $line
	# your code goes here
    done
}

# Stop port
# $1 - appliance ip
# $2 - port
function prj_appliance_stop_port() {
    local appliance=$1
    local port=$2
    local res=$(curl  --data "port=${port?:}" \
                      --verbose \
                      --write-out %{http_code} --silent --output /dev/null \
		      -H 'Content-Type: application/octet-stream' \
                      "http://${appliance:?}/app/stopPortList")
    if [ ! "${res:?}" -eq "200" ]
    then
        return err "port stopping failed. curl response: $res"
    fi
}

function prj_firmware() {
    prj_ls_firmwares_by_mtime | fzf
}
