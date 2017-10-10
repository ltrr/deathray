width = 400
height = 400

ptop = { 0, 0, 4 }
pfl  = { -1, -1, 0 }
pfr  = { 1, -1, 0 }
pbl  = { -1, 1, 0 }
pbr  = { 1, 1, 0 }

gfl  = { -2, -2, 0 }
gfr  = { 2, -2, 0 }
gbl  = { -2, 2, 0 }
gbr  = { 2, 2, 0 }

scene = mkscene {
    output_config = output_config {
        filename = "images/pyramid.ppm",
    },
    samples = 16,
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 2, 2, 2 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov = math.pi / 3,
        aspect = width / height
    },
    triangle {
        ptop, pfl, pfr,
        material = lambertian(color { 0.8, 0.8, 0.8 })
    },
    triangle {
        ptop, pfr, pbr,
        material = lambertian(color { 0.5, 0.8, 0.8 })
    },
    triangle {
        ptop, pbr, pbl,
        material = lambertian(color { 0.8, 0.8, 0.5 })
    },
    triangle {
        ptop, pbl, pfl,
        material = lambertian(color { 0.8, 0.5, 0.8 })
    },

    triangle {
        gfl, gfr, gbr,
        material = metal { albedo = color { 0.5, 0.5, 0.5 }, fuzz = 0.1 }
    },
    triangle {
        gfl, gbl, gbr,
        material = metal { albedo = color { 0.5, 0.5, 0.5 }, fuzz = 0.1 }
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    },
}
