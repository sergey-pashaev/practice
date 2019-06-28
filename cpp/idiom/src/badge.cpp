#include <iostream>

// Purpose of Badge template is that only T can call it's private ctor
// and nobody else, so only T can provide "badge".
template <typename T>
class Badge {
   private:
    friend T;
    Badge() = default;
};

// forward declaration
class AllowedServiceUser;

class ServiceProvider {
   public:
    // Here we allow to use publicly available method Service for
    // AllowedServiceUser only.
    int Service(Badge<AllowedServiceUser>, const AllowedServiceUser&) const {
        return 42;
    }
};

class AllowedServiceUser {
   public:
    int UseService(const ServiceProvider& provider) {
        // {} - constructs the "badge"
        return provider.Service({}, *this);
    }
};

class DisallowedServiceUser {
   public:
    int UseService(const ServiceProvider&) {
        // Won't compile: no viable conversion from 'DisallowedServiceUser' to
        // 'const AllowedServiceUser'
        // return provider.Service({}, *this);
        return 0;
    }
};

int main() {
    ServiceProvider provider;

    AllowedServiceUser allowed_user;
    allowed_user.UseService(provider);

    DisallowedServiceUser disallowed_user;
    disallowed_user.UseService(provider);
}
