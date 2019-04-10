
/*
    UVa 12412 - A Typical Homework (a.k.a Shi Xiong Bang Bang Mang)

    To build using Visual Studio 2015:
        cl -EHsc -O2 UVa_12412_A_Typical_Homework.cpp
*/

#include <vector>
#include <map>
#include <functional>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int sid_chrs = 10, max_cid = 20, max_name_chrs = 10, nr_scores = 4;
const double eps = 1.0e-5;

struct student {
    long long sid;
    int cid;
    char name[max_name_chrs + 1];
    int scores[nr_scores];
    int total, nr_passed;
};

vector<student> students;

struct score {
    int total;
    int nr, nr_passed, nr_failed;
};

struct statistic {
    int overall[nr_scores + 1]; // overall[i] is the number of students who passed i subjects
    score scores[nr_scores];
} statistics[max_cid + 1];

statistic& whole_statistic = statistics[0];

multimap<int, int, greater<int>> total_scores; // key is a total score, value is an index to students[]

void add_students()
{
    while (true) {
        puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
        char ssid[sid_chrs + 1];
        scanf("%s", ssid);
        if (!strcmp(ssid, "0"))
            return;
        student s;
        s.sid = strtoll(ssid, nullptr, 10);
        scanf("%d %s %d %d %d %d", &s.cid, s.name, &s.scores[0], &s.scores[1], &s.scores[2], &s.scores[3]);
        size_t i, n = students.size();
        for (i = 0; i < n; i++)
            if (s.sid == students[i].sid)
                break;
        if (i < n) {
            puts("Duplicated SID.");
            continue;
        }
        s.total = 0, s.nr_passed = 0;
        statistic& st = statistics[s.cid];
        for (int i = 0; i < nr_scores; i++) {
            s.total += s.scores[i], st.scores[i].total += s.scores[i], st.scores[i].nr++,
                whole_statistic.scores[i].total += s.scores[i], whole_statistic.scores[i].nr++;;
            if (s.scores[i] >= 60)
                s.nr_passed++, st.scores[i].nr_passed++, whole_statistic.scores[i].nr_passed++;
            else
                st.scores[i].nr_failed++, whole_statistic.scores[i].nr_failed++;
        }
        st.overall[s.nr_passed]++, whole_statistic.overall[s.nr_passed]++;
        students.push_back(s);
        total_scores.insert(make_pair(s.total, n));
    }
}

void remove_student(int si)
{
    student& s = students[si];
    statistic& st = statistics[s.cid];
    for (int i = 0; i < nr_scores; i++) {
        st.scores[i].total -= s.scores[i], st.scores[i].nr--,
            whole_statistic.scores[i].total -= s.scores[i], whole_statistic.scores[i].nr--;
        if (s.scores[i] >= 60)
            st.scores[i].nr_passed--, whole_statistic.scores[i].nr_passed--;
        else
            st.scores[i].nr_failed--, whole_statistic.scores[i].nr_failed--;
    }
    st.overall[s.nr_passed]--, whole_statistic.overall[s.nr_passed]--;
    for (auto j = total_scores.begin(); j != total_scores.end(); ) {
        if (j->second == si)
            total_scores.erase(j++);
        else {
            if (j->second > si)
                j->second--;
            ++j;
        }
    }
}

void remove_students()
{
    while (true) {
        puts("Please enter SID or name. Enter 0 to finish.");
        char sid_or_name[sid_chrs + 1];
        scanf("%s", sid_or_name);
        if (!strcmp(sid_or_name, "0"))
            return;
        int nr_removed = 0;
        if (isdigit(sid_or_name[0])) { // sid
            long long sid = strtoll(sid_or_name, nullptr, 10);
            for (auto i = students.begin(); i != students.end(); ) {
                if (i->sid == sid) {
                    remove_student(i - students.begin());
                    students.erase(i);
                    nr_removed++;
                    break;
                }
                else
                    ++i;
            }
        }
        else { // name
            for (auto i = students.begin(); i != students.end(); ) {
                if (!strcmp(i->name, sid_or_name)) {
                    remove_student(i - students.begin());
                    students.erase(i);
                    nr_removed++;
                }
                else
                    ++i;
            }
        }
        printf("%d student(s) removed.\n", nr_removed);
    }
}

void query_student(int si, int rank)
{
    const student& s = students[si];
    printf("%d %010lld %d %s %d %d %d %d %d %.2lf\n",
        rank, s.sid, s.cid, s.name, s.scores[0], s.scores[1], s.scores[2], s.scores[3],
        s.total, s.total / 4.0 + eps);
}

void query_students()
{
    map<int, int> ranks; // key is an index to students[], value is the rank

    int n = 0, rank = 0, score = -1;
    for (auto i = total_scores.cbegin(); i != total_scores.cend(); i++) {
        n++;
        if (i->first != score) {
            rank = n;
            score = i->first;
        }
        ranks.insert(make_pair(i->second, rank));
    }
    while (true) {
        puts("Please enter SID or name. Enter 0 to finish.");
        char sid_or_name[sid_chrs + 1];
        scanf("%s", sid_or_name);
        if (!strcmp(sid_or_name, "0"))
            return;
        if (isdigit(sid_or_name[0])) { // sid
            long long sid = strtoll(sid_or_name, nullptr, 10);
            for (size_t i = 0, n = students.size(); i < n; i++)
                if (students[i].sid == sid) {
                    query_student(i, ranks[i]);
                    break;
                }
        }
        else { // name
            for (size_t i = 0, n = students.size(); i < n; i++)
                if (!strcmp(students[i].name, sid_or_name))
                    query_student(i, ranks[i]);
        }
    }
}

void show_statistics(void)
{
    const char* courses[nr_scores] = {"Chinese", "Mathematics", "English", "Programming"};
    puts("Please enter class ID, 0 for the whole statistics.");
    int cid;
    scanf("%d", &cid);
    statistic& st = statistics[cid];
    for (int i = 0; i < nr_scores; i++) {
        const score& sc = st.scores[i];
        printf("%s\n", courses[i]);
        printf("Average Score: %.2lf\n", ((sc.nr) ? static_cast<double>(sc.total) / sc.nr : 0.0) + eps);
        printf("Number of passed students: %d\n", sc.nr_passed);
        printf("Number of failed students: %d\n\n", sc.nr_failed);
    }
    int overall = st.overall[4];
    printf("Overall:\nNumber of students who passed all subjects: %d\n", overall);
    overall += st.overall[3];
    printf("Number of students who passed 3 or more subjects: %d\n", overall);
    overall += st.overall[2];
    printf("Number of students who passed 2 or more subjects: %d\n", overall);
    overall += st.overall[1];
    printf("Number of students who passed 1 or more subjects: %d\n", overall);
    printf("Number of students who failed all subjects: %d\n\n", st.overall[0]);
}

#ifdef DEBUG
void print_students()
{
    for (size_t i = 0, n = students.size(); i < n; i++) {
        const student& s = students[i];
        if (s.sid != -1)
            printf("%d: %010lld %d %s %d %d %d %d %d %.2lf\n",
                i, s.sid, s.cid, s.name, s.scores[0], s.scores[1], s.scores[2], s.scores[3],
                s.total, s.total / 4.0 + eps);
    }
    for (auto j = total_scores.cbegin(); j != total_scores.cend(); ++j)
        printf("%d %d\n", j->first, j->second);
}
#endif

int main()
{
    while (true) {
        puts("Welcome to Student Performance Management System (SPMS).\n\n"
            "1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n");
        int c, sc;
        scanf("%d", &c);
        switch (c) {
        case 0:
            break;
        case 1:
            add_students();
#ifdef DEBUG
            print_students();
#endif
            break;
        case 2:
            remove_students();
#ifdef DEBUG
            print_students();
#endif
            break;
        case 3:
            query_students();
            break;
        case 4:
            puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
            break;
        case 5:
            show_statistics();
            break;
        }
        if (!c)
            break;
    }
    return 0;
}

