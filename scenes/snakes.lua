width = 800
height = 400

mat = lambertian { 0.8, 0.2, 0.2 }

n = 40

scene = {
    samples = 8,
    output_config = output_config {
        filename = "images/snakes.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { n/2, 2, -3 },
        target = { n/2, 0, n/2 },
        up = { 0, 1, 0 },
        fov = math.pi / 2,
        aspect = width / height
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}


k = 30

pi = math.pi
t = 10
g = 10
amp = 0.3
for j=1,k do
    for i=1,n do
        z = i
        L = 1 + (i/10)
        T = 2 * pi * math.sqrt(L/g)
        theta = amp * math.cos(2*pi*j/T + pi)
        --y = L * math.sin(theta)
        y = 0

        scene[#scene+1] = sphere {
            center = { j, y, z },
            radius = 0.5,
            material = lambertian (color {
                (j-1) / k, 0, 1 - ((j-1) / k)
            })
        }

        scene[#scene+1] = sphere {
            center = { j, 4 - y, z },
            radius = 0.5,
            material = lambertian (color {
                0, 1 - ((j-1) / k), (j-1) / k
            })
        }
    end
end

scene = mkscene(scene)
