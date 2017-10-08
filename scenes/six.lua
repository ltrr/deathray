width = 400
height = 400

mat = {}
mat[1] = lambertian { 0.8, 0.5, 0.5 }
mat[2] = lambertian { 0.8, 0.8, 0.5 }
mat[3] = lambertian { 0.5, 0.8, 0.5 }
mat[4] = lambertian { 0.5, 0.8, 0.8 }
mat[5] = lambertian { 0.5, 0.5, 0.8 }
mat[6] = lambertian { 0.8, 0.5, 0.8 }


scene = {
    samples = 16,
    output_config = output_config {
        filename = "images/six.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 0, 4, 0 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov = math.pi / 2,
        aspect = width / height
    },
    bg = sky {
        zenith = { 0.8, 0.8, 0.9 },
        nadir = { 0.5, 0.7, 1 }
    }
}

for i=1,6 do
    ang = i * math.pi / 3
    scene[i] = sphere {
        center = { 2 * math.cos(ang), 0, 2 * math.sin(ang) },
        radius = 1,
        material = mat[i]
    }
end

scene = mkscene(scene)
