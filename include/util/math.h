#ifndef DEATHRAY_UTIL_MATH_H_
#define DEATHRAY_UTIL_MATH_H_

#include <cmath>
#include <limits>
#include <tuple>

const float FLOAT_MAX = std::numeric_limits<float>::max();
const float FLOAT_INF = std::numeric_limits<float>::infinity();
const float FLOAT_EPS = std::numeric_limits<float>::epsilon();

const float PI = acos(-1);
const float TWO_PI = 2 * PI;

static std::tuple<int, float, float> quadratic(float a, float bb, float c)
{
    using std::make_tuple;

    float delta = bb*bb - a*c;
    if (delta >= 0) {
        float d = sqrt(delta);
        if (bb > 0) {
            float e = -(bb + d);
            return make_tuple(2, c/e, e/a);
        }
        else if (bb < 0) {
            float e = -bb + d;
            return make_tuple(2, e/a, c/e);
        }
        else if (abs(a) > abs(c)) {
            return make_tuple(2, d/a, -d/a);
        }
        else {
            return make_tuple(2, -c/d, c/d);
        }
    }
    else {
        return make_tuple(0, 0.0f, 0.0f);
    }

    /*
    b = b*.5
    delta = delta or b*b-a*c
    if delta >= 0. then
        local d = math.sqrt(delta)
        if b > 0. then
            local e = b+d
            return 2, -c, e, e, -a
        elseif b < 0. then
            local e = -b+d
            return 2, e, a, c, e
        elseif abs(a) > abs(c) then
            return 2, d, a, -d, a
        else
            return 2, -c, d, c, d
        end
    else
        return 0
    end
    */
}

#endif // DEATHRAY_UTIL_MATH_H_
