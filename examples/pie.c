#include "matplotc.h"

int main(void)
{
    Context window = create_context(
        800.0,
        800.0,
        "MatplotC - Pie Chart Test"
    );

    if (window.width == 0) {
        return 1;
    }

    Plane plano = {
        {0, 4}, 1,
        {0, 100}, 10,
        false
    };

    int x1[] = {1, 2, 3, 4};
    int y1[] = {40, 30, 20, 10};

    int size1 = sizeof(y1) / sizeof(y1[0]);

    Data data1 = create_data(
        plano,
        "Languages",
        x1,
        "Language",
        y1,
        "Participation (%)",
        size1
    );

    if (data1.size == 0) {
        return 1;
    }

    Data data[] = {data1};
    int data_count = sizeof(data) / sizeof(data[0]);

    plot_pie(&window, &plano, data, data_count);

    return 0;
}
