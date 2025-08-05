#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

class GoodRead {
public:
    void Read(int id, int page) {
        if (users_.count(id)) {
            int old_page = users_[id];
            page_count_[old_page]--;
        }
        users_[id] = page;
        page_count_[page]++;
    }
    void Cheer(int id) {
        if (!users_.count(id) || GetUsers() == 1) {
            std::cout << (users_.count(id) ? "1" : "0") << std::endl;
        } else {
            int my_page = users_[id];
            int less = 0;
            for (auto it = page_count_.begin(); it != page_count_.end() && it->first < my_page; ++it) {
                less += it->second;
            }
            int others = users_.size() - 1;
            double result = static_cast<double>(less) / others;
            std::cout << std::setprecision(6) << result << std::endl;
        }
    }

private:
    std::map<int, int> users_;
    std::map<int, int> page_count_;

    int GetUsers() {
        return users_.size();
    }
};

int main() {
    GoodRead reader;
    int requests{0};
    std::cin >> requests;
    std::cin.ignore();
    while (requests) {
        std::string query;
        std::getline(std::cin, query);
        std::istringstream istr(query);
        std::string line;
        istr >> line;
        if (line == "READ") {
            int id, pages;
            istr >> id >> pages;
            reader.Read(id, pages);
        } else {
            int id;
            istr >> id;
            reader.Cheer(id);
        }
        --requests;
    }
    return 0;
}