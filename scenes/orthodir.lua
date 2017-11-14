width = 400
height = 400

cube = loadobj("assets/mesh/opencube.obj")

scene = mkscene {
    output_config = output_config {
        filename = "images/orthodir.ppm",
    },
    samples = 16,
    viewport = mkviewport {
        width = width,
        height = height
    },
    orthocam {
        position = { -1, 1, -1.1 },
        target = { -1, 1, -1 },
        up = { 0, 1, 0 },
        width = 5,
        height = 5,
        direction = { .5, -.5, 1 }
    },

    cube,
    transform.translate({0, 0, 2}, cube),

    bg = sky {
        zenith = { .7, .2, .2 },
        nadir = { .2, .2, .7 }
    },
}
