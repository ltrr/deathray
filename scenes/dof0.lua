width = 1200
height = 600
mat = lambertian(color { 0.5, 0.5, 0.5 })

scene = mkscene {
    samples = 64,
    output_config = output_config {
        filename = "images/dof0.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { -2, 0, 0 },
        target = { 0, 0, -2 },
        up = { 0, 1, 0 },
        fov = math.pi / 3,
        aspect = width / height,
        f = 2*math.sqrt(2),
        aperture = 0,
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 1, 1, 1 }
    },
    plane {
        point = {0, -.5, -1},
        normal = {0, 1, 0},
        material = mat
    },
    sphere {
        center = { 0, 0, -1 },
        radius = 0.5,
        material = lambertian(color { 0.8, 0.5, 0.5 })
    },
    sphere {
        center = { 0, 0, -2 },
        radius = 0.5,
        material = lambertian { albedo = texture.checkers() }
    },
    sphere {
        center = { 0, 0, -3 },
        radius = 0.5,
        material = lambertian(color { 0.8, 0.5, 0.8 })
    },
    sphere {
        center = { 0, 0, -4 },
        radius = 0.5,
        material = lambertian(color { 0.8, 0.8, 0.5 })
    },
}
