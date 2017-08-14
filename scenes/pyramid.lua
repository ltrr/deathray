name = "images/pyramid.ppm"
type = "ppm"
codification = "binary"
width = 400
height = 400


samples = 8

viewport = mkviewport {
    width = width,
    height = height
}

camera = lookat {
    origin = { -20, -20, 40 },
    target = { 0, 0, 0.5 },
    up = { 0, 0, 1 },
    fov = math.pi * 0.7,
    aspect = width / height
}

ptop = { 0, 0, 3 }
pfl  = { -1, -1, 0 }
pfr  = { 1, -1, 0 }
pbl  = { -1, 1, 0 }
pbr  = { 1, 1, 0 }

gfl  = { -3, -3, 0 }
gfr  = { 3, -3, 0 }
gbl  = { -3, 3, 0 }
gbr  = { 3, 3, 0 }

scene = mkscene {
    triangle {
        ptop, pfl, pfr,
        material = lambert { 0.8, 0.5, 0.5 }
    },
    triangle {
        ptop, pfr, pbr,
        material = lambert { 0.5, 0.8, 0.5 }
    },
    triangle {
        ptop, pbr, pbl,
        material = lambert { 0.5, 0.5, 0.8 }
    },
    triangle {
        ptop, pbl, pfl,
        material = lambert { 0.8, 0.5, 0.8 }
    },

    triangle {
        gfl, gfr, gbr,
        material = metal { albedo = { 0.5, 0.5, 0.5 }, fuzz = 0.2 }
    },
    triangle {
        gfl, gbl, gbr,
        material = metal { albedo = { 0.5, 0.5, 0.5 }, fuzz = 0.2 }
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
