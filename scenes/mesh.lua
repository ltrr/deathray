width = 400
height = 400

scene = mkscene {
    samples = 64,
    output_config = output_config {
        filename = "images/mesh.ppm",
    },
    loadobj("assets/mesh/suzane.obj"),
    lookat {
        origin = { -1.5, 0.5, 1.5 },
        target = { 0, 0, 0 },
        up = { 0, 1, 0 },
        fov = math.pi * 0.5,
        aspect = width / height
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    bg = sky {
        zenith = { 0.7, 0.7, 1 },
        nadir = { 1, 1, 1 }
    }
}
