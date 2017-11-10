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


pyramid = {
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
    }
}


scene = mkscene {
    output_config = output_config {
        filename = "images/pyramids.ppm",
    },
    samples = 16,
    viewport = mkviewport {
        width = width,
        height = height
    },
    orthocam {
        position = { 10, 10, 10 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        width = 10,
        height = 10
    },

    transform.translate({0, 0, 0}, pyramid),
    transform.translate({3, 0, 0}, pyramid),
    transform.translate({-3, 0, 0}, pyramid),

    plane {
        position = {0,0,0},
        normal = {0,0,1},
        material = lambertian(color { 0.76, 0.69, 0.5 })
    },

    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    },
}
