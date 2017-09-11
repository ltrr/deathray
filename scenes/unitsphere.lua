width = 400
height = 400

scene = mkscene {
    output_config = output_config {
        filename = "images/unitsphere.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 0, 2, 0 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov =  math.pi / 2,
        aspect = width / height
    },
    sphere {
        center = {0,0,0},
        radius = 1,
        material = lambert { 0.5, 0.5, 0.5 }
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
