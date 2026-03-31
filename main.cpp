#include <bits/stdc++.h>
using namespace std;

struct Student {
    string id;
    string name;
    int score;
    int insert_idx; // to preserve insertion order where required
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Student> students; // maintain insertion order
    unordered_map<string, int> id_to_index; // map id to index in students
    unordered_map<string, int> name_to_index; // map name to index in students
    id_to_index.reserve(10007);
    name_to_index.reserve(10007);

    int cmd;
    int insert_counter = 0;
    while ( (cin >> cmd) ) {
        if (cmd == 1) {
            string id, name; int score;
            if (!(cin >> id >> name >> score)) return 0;
            if (id_to_index.find(id) != id_to_index.end()) {
                cout << "FAILED\n";
                continue;
            }
            Student s{ id, name, score, insert_counter++ };
            students.push_back(s);
            int idx = (int)students.size() - 1;
            id_to_index[id] = idx;
            name_to_index[name] = idx;
            cout << "SUCCESS\n";
        } else if (cmd == 2) {
            // display all in insertion order (students vector order)
            if (!students.empty()) {
                for (const auto &s : students) {
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 3) {
            string id; cin >> id;
            int idx = id_to_index[id];
            const auto &s = students[idx];
            cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
        } else if (cmd == 4) {
            string name; cin >> name;
            int idx = name_to_index[name];
            const auto &s = students[idx];
            cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
        } else if (cmd == 5) {
            // sort by id ascending, stable not required but we can keep stable by id
            if (!students.empty()) {
                vector<int> idx(students.size());
                iota(idx.begin(), idx.end(), 0);
                stable_sort(idx.begin(), idx.end(), [&](int a, int b){
                    return students[a].id < students[b].id;
                });
                for (int i : idx) {
                    const auto &s = students[i];
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 6) {
            // sort by score descending; when equal, by insertion order (insert_idx ascending)
            if (!students.empty()) {
                vector<int> idx(students.size());
                iota(idx.begin(), idx.end(), 0);
                stable_sort(idx.begin(), idx.end(), [&](int a, int b){
                    if (students[a].score != students[b].score)
                        return students[a].score > students[b].score;
                    return students[a].insert_idx < students[b].insert_idx;
                });
                for (int i : idx) {
                    const auto &s = students[i];
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 7) {
            cout << "END\n";
            break;
        } else {
            // unknown command: ignore rest of line, continue
            string line;
            getline(cin, line);
        }
    }

    return 0;
}

