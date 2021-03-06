width = 800
height = 400

diamond = loadobj("assets/mesh/diamond.obj")

scene = mkscene {
    output_config = output_config {
        filename = "images/transform1.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 15, -10, 0 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov =  math.pi / 4,
        aspect = width / height
    },

    transform.translate({0, -4, 2},
        transform.scale({1, 1, 1}, diamond)
    ),
    transform.translate({0, -2, 2},
        transform.scale({.8, 1, 1}, diamond)
    ),
    transform.translate({0, 0, 2},
        transform.scale({.5, 1, 1}, diamond)
    ),
    transform.translate({0, 2, 2},
        transform.scale({.3, 1, 1}, diamond)
    ),
    transform.translate({0, 4, 2},
        transform.scale({.1, 1, 1}, diamond)
    ),


    transform.translate({0, -4, 0},
        transform.scale({1, 1, 1}, diamond)
    ),
    transform.translate({0, -2, 0},
        transform.scale({1, .8, 1}, diamond)
    ),
    transform.translate({0, 0, 0},
        transform.scale({1, .5, 1}, diamond)
    ),
    transform.translate({0, 2, 0},
        transform.scale({1, .3, 1}, diamond)
    ),
    transform.translate({0, 4, 0},
        transform.scale({1, .1, 1}, diamond)
    ),


    transform.translate({0, -4, -2},
        transform.scale({1, 1, 1}, diamond)
    ),
    transform.translate({0, -2, -2},
        transform.scale({1, 1, .8}, diamond)
    ),
    transform.translate({0, 0, -2},
        transform.scale({1, 1, .5}, diamond)
    ),
    transform.translate({0, 2, -2},
        transform.scale({1, 1, .3}, diamond)
    ),
    transform.translate({0, 4, -2},
        transform.scale({1, 1, .1}, diamond)
    ),

    samples = 8,

    --transform.rotate({1, 0, 0}, math.pi/4, diamond),
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
