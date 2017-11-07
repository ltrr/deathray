width = 400
height = 400

floor_mat = lambertian {
    albedo = color { 0.5, 0.5, 0.5 },
}

light_mat = lambertian {
    emission = color { 1, 1, 1 }
}

scene = mkscene {
    output_config = output_config {
        filename = "images/slit.ppm",
    },
    samples = 1,
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { -2, 1, 0 },
        target = { 0, 1, 0 },
        up = { 0, 1, 0 },
        fov = math.pi / 2,
        aspect = width / height
    },

    -- floor
    triangle {
        {-1, 0, -1}, {-1, 0, 1}, {1, 0, -1},
        material = floor_mat
    },
    triangle {
        {1, 0, 1}, {-1, 0, 1}, {1, 0, -1},
        material = floor_mat
    },

    -- ceiling
    triangle {
        {-1, 2, -1}, {-1, 2, 1}, {1, 2, -1},
        material = floor_mat
    },
    triangle {
        {1, 2, 1}, {-1, 2, 1}, {1, 2, -1},
        material = floor_mat
    },

    -- left wall
    triangle {
        {-1, 0, -1}, {-1, 2, -1}, {1, 0, -1},
        material = floor_mat
    },
    triangle {
        {1, 2, -1}, {-1, 2, -1}, {1, 0, -1},
        material = floor_mat
    },

    -- right wall
    triangle {
        {-1, 0, 1}, {-1, 2, 1}, {1, 0, 1},
        material = floor_mat
    },
    triangle {
        {1, 2, 1}, {-1, 2, 1}, {1, 0, 1},
        material = floor_mat
    },

    triangle {
        {1, 0, -1}, {1, 0, 1}, {1, 2, -1},
        material = light_mat
    },
    triangle {
        {1, 2, 1}, {1, 0, 1}, {1, 2, -1},
        material = light_mat
    },

    triangle {
        {0, 0, 0.1}, {0, 0, 1}, {0, 2, 0.1},
        material = floor_mat
    },
    triangle {
        {0, 2, 1}, {0, 0, 1}, {0, 2, 0.1},
        material = floor_mat
    },

    triangle {
        {0, 0, -0.1}, {0, 0, -1}, {0, 2, -0.1},
        material = floor_mat
    },
    triangle {
        {0, 2, -1}, {0, 0, -1}, {0, 2, -0.1},
        material = floor_mat
    },
    spherevolume {
        center = {0,0,0},
        radius = 10,
        density = 10,
        material = lambertian { 1, 1, 1 }
    },
    bg = sky {
        zenith = { 0, 0, 0 },
        nadir = { 0, 0, 0 }
    }
}
