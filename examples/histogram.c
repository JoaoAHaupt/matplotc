#include "matplotc.h"

int main(void)
{
    Context window = create_context(
        1200.0,
        800.0,
        "Measurement Distribution"
    );

    if (window.width == 0) {
        return 1;
    }

    Plane plane = create_plane(
        0, 100, 10.0f,
        0, 10, 1.0f,
        false
    );

    int measurements[] = {
        12, 18, 22, 27, 31, 34, 38, 42, 45, 47,
        51, 53, 56, 59, 62, 65, 68, 71, 74, 78,
        82, 86, 91, 95
    };
    int sample_indices[sizeof(measurements) / sizeof(measurements[0])];
    int sample_count = (int)(sizeof(measurements) / sizeof(measurements[0]));

    for (int i = 0; i < sample_count; i++) {
        sample_indices[i] = i;
    }

    Data measurements_data = create_data(
        plane,
        "Measurements",
        measurements,
        "Measurement",
        sample_indices,
        "Frequency",
        sample_count
    );

    if (measurements_data.size == 0) {
        return 1;
    }

    plot_histogram(&window, &plane, &measurements_data, 1);
    return 0;
}
