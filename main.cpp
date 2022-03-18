#include <iostream>
#include <vector>
#include <random>
#include <bits/stdc++.h>
using namespace std;

struct item
{
    int id;
    int weight;
    int value;
};

struct bag
{
    int id;
    int weight;
    int value;
    vector<int> items;
};

bool compare_items(bag b1, bag b2)
{
    return (b1.value > b2.value);
}

int exhaustive_search(int W, vector<item> items, int position)
{
    int r1 = 0;
    int r2 = 0;

    if (position < int (items.size()))
    {
        if (W - items[position].weight >= 0)
        {
            r1 = items[position].value + exhaustive_search(W-items[position].weight, items, position + 1);
        }
        
        r2 = exhaustive_search(W, items, position + 1);
        return max(r1,r2);
    } else
    {
        if (W - items[position].weight >= 0) {
            return items[position].value;
        } else {
            return 0;
        }
    }
}

int main ()
{
    vector<item> items;
    vector<bag> bags;
    int max_items, max_weight;

    cin >> max_items >> max_weight;
    bags.reserve(max_items);
    
    for (int i=0; i<max_items; i++)
    {
        item temp;
        cin >> temp.weight >> temp.value;
        temp.id = i;
        items.push_back(temp);
    }

    int _exhaustive_search = exhaustive_search(max_weight, items, 0);

    cout << _exhaustive_search << endl; 

    return 0;
}