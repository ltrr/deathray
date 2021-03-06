#include "material/dieletric.h"

#include "surface/surface.h"
#include "util/random.h"


float schlick(float cos_, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 *= r0;
    return r0 + (1-r0)*pow((1-cos_), 5);
}


bool Dieletric::scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const
{
    Vec3 out_n;
    float ni_nt;
    float refl_prob;
    float cos_;

    float inc = dot(in, hit.normal);
    if (inc > 0) {
        out_n = -hit.normal;
        ni_nt = refract_index_;
        cos_ = refract_index_ * inc / len(in);
    }
    else {
        out_n = hit.normal;
        ni_nt = 1.0 / refract_index_;
        cos_ = (-inc / len(in));
    }

    Vec3 refracted;
    if (refract(in, out_n, ni_nt, refracted)) {
        refl_prob = schlick(cos_, refract_index_);
    }
    else {
        scattered = reflect(in, hit.normal);
        return true;
    }

    if (randf() < refl_prob) {
        scattered = reflect(in, hit.normal);
    }
    else {
        scattered = refracted;
    }
    return true;
}
