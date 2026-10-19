#include "matplotc.h"

int main(void)
{
    Context window = create_context(
        1200.0,
        800.0,
        "Monthly Sales - Store Comparison"
    );

    if (window.width == 0) {
        return 1;
    }

    Plane plane = {
        {1, 6}, 1,
        {0, 100}, 10,
        false
    };

    int x1[] = {1, 2, 3, 4, 5, 6};
    int y1[] = {45, 52, 48, 65, 72, 80};

    int size1 = sizeof(x1) / sizeof(x1[0]);

    Data data1 = create_data(
        plane,
        "Downtown Store",
        x1,
        "Months",
        y1,
        "Sales (R$ thousands)",
        size1
    );

    if (data1.size == 0) {
        return 1;
    }

    Data data[] = {data1};
    int data_count = sizeof(data) / sizeof(data[0]);

    plot_bar(&window, &plane, data, data_count);

    return 0;
}
