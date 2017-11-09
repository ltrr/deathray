width = 400
height = 400

mat = {}
mat[1] = lambertian(color { 0.8, 0.5, 0.5 })
mat[2] = lambertian(color { 0.8, 0.8, 0.5 })
mat[3] = lambertian(color { 0.5, 0.8, 0.5 })

scene = mkscene {
    samples = 16,
    output_config = output_config {
        filename = "images/planes.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 1, 1, 1 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov = math.pi / 2,
        aspect = width / height
    },
    bg = sky {
        zenith = { 0.8, 0.8, 0.9 },
        nadir = { 0.5, 0.7, 1 }
    },
    plane {
        point = {0, 0, 0},
        normal = {1, 0, 0},
        material = mat[1]
    },
    plane {
        point = {0, 0, 0},
        normal = {0, 1, 0},
        material = mat[2]
    },
    plane {
        point = {0, 0, 0},
        normal = {0, 0, 1},
        material = mat[3]
    }
}
