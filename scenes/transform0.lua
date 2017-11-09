width = 800
height = 400

diamond = loadobj("assets/mesh/diamond.obj")

scene = mkscene {
    output_config = output_config {
        filename = "images/transform0.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 15, 0, 0 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov =  math.pi / 4,
        aspect = width / height
    },

    transform.translate({0, -4, 2},
        transform.rotate({1, 0, 0}, -math.pi/2, diamond)
    ),
    transform.translate({0, -2, 2},
        transform.rotate({1, 0, 0}, -math.pi/4, diamond)
    ),
    transform.translate({0, 0, 2},
        transform.rotate({1, 0, 0}, 0, diamond)
    ),
    transform.translate({0, 2, 2},
        transform.rotate({1, 0, 0}, math.pi/4, diamond)
    ),
    transform.translate({0, 4, 2},
        transform.rotate({1, 0, 0}, math.pi/2, diamond)
    ),


    transform.translate({0, -4, 0},
        transform.rotate({0, 1, 0}, -math.pi/2, diamond)
    ),
    transform.translate({0, -2, 0},
        transform.rotate({0, 1, 0}, -math.pi/4, diamond)
    ),
    transform.translate({0, 0, 0},
        transform.rotate({0, 1, 0}, 0, diamond)
    ),
    transform.translate({0, 2, 0},
        transform.rotate({0, 1, 0}, math.pi/4, diamond)
    ),
    transform.translate({0, 4, 0},
        transform.rotate({0, 1, 0}, math.pi/2, diamond)
    ),


    transform.translate({0, -4, -2},
        transform.rotate({0, 0, 1}, -math.pi/2, diamond)
    ),
    transform.translate({0, -2, -2},
        transform.rotate({0, 0, 1}, -math.pi/4, diamond)
    ),
    transform.translate({0, 0, -2},
        transform.rotate({0, 0, 1}, 0, diamond)
    ),
    transform.translate({0, 2, -2},
        transform.rotate({0, 0, 1}, math.pi/4, diamond)
    ),
    transform.translate({0, 4, -2},
        transform.rotate({0, 0, 1}, math.pi/2, diamond)
    ),

    samples = 16,

    --transform.rotate({1, 0, 0}, math.pi/4, diamond),
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
