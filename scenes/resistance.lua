-- EYE OF THE RESISTENCE --
width = 1920
height = 960

-- scene configuration
scene = {
    samples = 1,
    output_config = output_config {
        filename = "images/resistance.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 0, -2, 0 },
        target = { 0, 0, 0 },
        up = { 0, 0, 1 },
        fov = 0.65 * math.pi,
        aspect = width / height
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 1, 1, 1 }
    }
}


-- converts hsv to rgb
function hsv(h, s, v)
    h = h % 360
    c = v * s
    x = c * (1 - math.abs((h / 60) % 2 - 1))
    m = v - c
    r_ = 0
    g_ = 0
    b_ = 0
    if h < 60 then
        r_ = c
        g_ = x
    elseif h < 120 then
        r_ = x
        g_ = c
    elseif h < 180 then
        g_ = c
        b_ = x
    elseif h < 240 then
        g_ = x
        b_ = c
    elseif h < 300 then
        r_ = x
        b_ = c
    else
        r_ = c
        b_ = x
    end
    return { r_ + m, g_ + m, b_ + m }
end

math.randomseed(3)

layers = 30   -- cylinder
stops = 32    -- spheres per circunference
step = (360 / stops)
R = 3         -- cylinder radius
r = 2 * math.pi / stops -- cylinder thickness

h_spr = 30     -- hue angle spread
hole_p = 0.4   -- removal probability near the camera
hole_pf = 0.05 -- removal probability far from camera


-- small spheres cylinder
for i = 1, layers do
    for j = 1, stops do

        d = i/layers

        -- removes some spheres
        -- more likely close to the camera
        if math.random() > (1-d)*hole_p + d*hole_pf then
            theta = step * j
            if i % 2 == 1 then
                theta = theta + step/2
            end

            theta_ = math.rad(theta)
            x = R * math.sin(theta_)
            z = R * math.cos(theta_)

            -- angle defines
            h = (theta + math.random(-h_spr, h_spr) + 180) % 360
            v = 0.4 * d + 0.2 * math.random() + 0.4
            s = 0.4 * d + 0.2 * math.random() + 0.4

            scene[#scene+1] = sphere {
                center = { x, i * r, z },
                radius = r,
                material = lambert(hsv(h, s, v))
            }
        end
    end
end


-- main sphere (sclera)
scene[#scene+1] = sphere {
    center = { 0, r * layers, 0 },
    radius = 0.9 * R,
    material = metal { albedo = { 1, 1, 1 }, fuzz = 0 }
}

-- black sphere behind the camera (pupil)
scene[#scene+1] = sphere {
    center = { 0, -80, 0 },
    radius = 40,
    material = lambert { 0.1, 0.1, 0.1 }
}

-- bg sphere
scene[#scene+1] = sphere {
    center = { 0, R+300, 0 },
    radius = 280,
    material = lambert { 0, 0, 54/255 }
}


scene = mkscene(scene)
