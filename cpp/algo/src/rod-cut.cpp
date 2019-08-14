#include <iostream>
#include <vector>

using std::vector;
using std::cout;

struct CutCost {
    int length = 0;
    int cost = 0;
};

typedef vector<CutCost> Prices;

class RodCutEstimator {
   public:
    RodCutEstimator(int length, const Prices& prices) : prices_(prices) {
        table_.resize(length + 1, 0);  // 1 for zero length
        cuts_.resize(length + 1, 0);

        // init table with given prices
        for (auto& i : prices_) {
            table_[i.length] = i.cost;
        }

        for (size_t i = 0; i < table_.size(); ++i) {
            Estimate(i);
        }
    }

    int MaxCost() const { return table_.back(); }

    vector<int> Cuts() const {
        vector<int> ret;
        size_t last = table_.size() - 1;
        while (cuts_[last] != 0) {
            ret.push_back(cuts_[last]);
            last -= cuts_[last];
        }
        ret.push_back(last);
        return ret;
    }

   private:
    int Estimate(int length) {
        if (length == 0) return 0;

        int max = table_[length];
        int max_cut = 0;
        for (auto& p : prices_) {
            // if possible to make a cut
            if (p.length < length) {
                // calc current cut cost as: current cut cost + best cost of
                // leftovers
                int cost = p.cost + table_[length - p.length];
                // save best cut
                if (cost > max) {
                    max = cost;
                    max_cut = p.length;
                }
            }
        }

        table_[length] = max;
        cuts_[length] = max_cut;
        return table_[length];
    }

    Prices prices_;
    vector<int> table_;
    vector<int> cuts_;
};

int main() {
    const size_t length = 200;
    const vector<CutCost> prices = {{1, 1}, {2, 5}, {3, 8}, {4, 9}};
    RodCutEstimator r(length, prices);

    cout << "best cost: " << r.MaxCost() << '\n';
    auto cuts = r.Cuts();
    cout << "cuts: ";
    for (auto c : cuts) {
        cout << c << ' ';
    }
    cout << '\n';

    return 0;
}
