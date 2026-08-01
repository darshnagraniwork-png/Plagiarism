#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxActiveEvents(vector<pair<int, int>>& intervals) {
    vector<pair<int, int>> events;
    for (auto& interval : intervals) {
        events.push_back({interval.first, 1});   
        events.push_back({interval.second, -1});  
    }

    sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second; 
    });

    int max_active = 0, current_active = 0;
    for (auto& event : events) {
        current_active += event.second;
        max_active = max(max_active, current_active);
    }
    return max_active;
}