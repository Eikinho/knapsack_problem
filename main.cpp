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

struct Bag
{
    int id;
    int weight = 0;
    int value = 0;
    vector<item> items;
};

struct method
{
    // 1 - Heuristica; 2 - Aleatorizacao; 3 - Busca Local; 4 - Busca Exaustiva
    int id;
    Bag bag;
};

struct Cursor
{
    vector<item> items;
    int max_items;
    int max_weight;
    default_random_engine generator;
    uniform_real_distribution<double> distribution;
};

Cursor init_items()
{
    Cursor cursor;
    vector<item> items;

    int max_items, max_weight;

    cin >> max_items >> max_weight;
    
    for (int i=0; i<max_items; i++)
    {
        item temp;
        cin >> temp.weight >> temp.value;
        temp.id = i;
        items.push_back(temp);
    }

    cursor.max_items = max_items;
    cursor.max_weight = max_weight;
    cursor.items = items;

    return cursor;

}

bool compare_items(Bag b1, Bag b2)
{
    return (b1.value > b2.value);
}

bool compare_weight(item a, item b)
{
    return (a.weight < b.weight);
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

int local_search(Cursor cursor, int h)
{
    Bag bag;
    Bag better_bag;
    vector<item> items = cursor.items;
    int weight;
    int value;
    int bag_value;
    int bag_better_value;

    for (int i=0; i < h; i++)
    {
        bag.items.clear();
        for (auto& el:items)
        {
            double prob = cursor.distribution(cursor.generator);
            if (el.weight + weight <= cursor.max_weight and prob <=0.5)
            {
                bag.items.push_back(el);
                weight += el.weight;
                value += el.value;
            }
            bag_value += bag.items[i].value;
        }

        sort(bag.items.begin(), bag.items.end(), compare_weight);

        if (bag_value > bag_better_value)
        {
            better_bag = bag;
        }

        weight = 0;
        value = 0;
        bag_value = 0;
        bag.items.clear();
    }

    int beter_bag_sum = 0;
    for (auto& el: better_bag.items)
    {
        beter_bag_sum += better_bag.value;
    }


    return beter_bag_sum;
}

int heuristic(Cursor cursor)
{
    Bag bag;
    vector<item> items = cursor.items;default_random_engine generator(10);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    sort(items.begin(), items.end(), compare_weight);
    for (auto& el : items)
    {
        if (el.weight + bag.weight <= cursor.max_weight)
        {
            bag.items.push_back(el);
            bag.weight += el.weight;
            bag.value += el.value;
        }
    }

    sort(bag.items.begin(), bag.items.end(), [](auto& i, auto&j){return i.id < j.id;});

    return bag.value;
}

int randomization()
{

    return 0;
}

int main ()
{
    Cursor cursor;
    vector<Bag> bags;
    default_random_engine generator(10);
    cursor.generator = generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    cursor.distribution = distribution;
    
    cursor = init_items();

    int _exhaustive_search = exhaustive_search(cursor.max_weight, cursor.items, 0);
    int _heuristic = heuristic(cursor);
    int _local_search = local_search(cursor, 1000);

    cout << "Heuristic:" << _heuristic << endl;
    cout << "Exhaustive Search:" <<_exhaustive_search << endl;
    cout << "Busca Local: " << _local_search << endl;

    return 0;
}