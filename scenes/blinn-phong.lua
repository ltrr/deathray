name = "images/blinn-phong.ppm"
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
    origin = { 0, 0, -2 },
    target = { 0, 0, 0 },
    up = { 0, 1, 0 },
    fov = math.pi / 3,
    aspect = width / height
}

scene = mkscene {
    sphere {
        center = {-1,1,1},
        radius = .5,
        material = blinn_phong {
            diffuse = { 0.8, 0.2, 0.2 },
            specular = { 1, 1, 1 },
            ambient = { 0.0, 0.0, 0.0 },
            shiness = 128
        }
    },
    sphere {
        center = {1,1,1},
        radius = .5,
        material = blinn_phong {
            diffuse = { 0.2, 0.8, 0.2 },
            specular = { 1, 1, 1 },
            ambient = { 0.0, 0.0, 0.0 },
            shiness = 64
        }
    },
    sphere {
        center = {-1,-1,1},
        radius = .5,
        material = blinn_phong {
            diffuse = { 0.2, 0.2, 0.8 },
            specular = { 1, 1, 1 },
            ambient = { 0.0, 0.0, 0.0 },
            shiness = 32
        }
    },
    sphere {
        center = {1,-1,1},
        radius = .5,
        material = blinn_phong {
            diffuse = { 0.7, 0.7, 0.2 },
            specular = { 1, 1, 1 },
            ambient = { 0.0, 0.0, 0.0 },
            shiness = 16
        }
    },
    pointlight {
        position = { 0, 0, 0 },
        intensity = { 0.4, 0.4, 0.4 }
    },
    bg = sky {
        zenith = { 0.8, 0.8, 0.9 },
        nadir = { 0.5, 0.7, 1 }
    }
}

shader = blinn_phong_shader()
