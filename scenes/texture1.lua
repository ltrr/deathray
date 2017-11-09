width = 1200
height = 600

tex_sphere = sphere {
    center = { 0, 0, 0 },
    radius = 0.5,
    material = lambertian {
        albedo = texture.checkers()
    }
}

scene = mkscene {
    samples = 8,
    output_config = output_config {
        filename = "images/texture1.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 0, 0, 0 },
        target = { 0, 0, -1 },
        up = { 0, 1, 0 },
        fov = 2 * math.atan(2),
        aspect = width / height
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 1, 1, 1 }
    },
    sphere {
        center = { 0, -100.5, -3 },
        radius = 100,
        material = lambertian {
            albedo = color {.5, .5, .5}
        }
    },

    transform.translate({-1, 0, -1},
        transform.rotate({1, 0, 0}, 1, tex_sphere)),
    transform.translate({0, 0, -1},
        transform.rotate({0, 1, 0}, 1, tex_sphere)),
    transform.translate({1, 0, -1},
        transform.rotate({0, 0, 1}, 1, tex_sphere))
}
