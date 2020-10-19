#version 330

// CSci-4611 Assignment 5:  Art Render

in vec3 position_in_eye_space;
in vec3 normal_in_eye_space;

out vec4 color;

uniform vec3 light_in_eye_space;
uniform vec4 Ia, Id, Is;

uniform vec4 ka, kd, ks;
uniform float s;

uniform sampler2D diffuse_ramp;
uniform sampler2D specular_ramp;


void main() {
    // transform the vertex position into "eye space"
    vec3 v = position_in_eye_space;

    // unit vector from the vertex to the light
    vec3 l = normalize(light_in_eye_space - v);

    // unit vector from the vertex to the eye point, which is at 0,0,0 in "eye space"
    vec3 e = normalize(vec3(0, 0, 0) - v);

    // normal transformed into "eye space"
    vec3 n = normalize(normal_in_eye_space);

    // reflection vector
    vec3 h = normalize(l + e);




    // calculating lighting output the color for this vertex
    vec4 ambient = ka * Ia;

    float diff_calc = dot(n, l);
    vec2 diff_tex = vec2(diff_calc * 0.5 + 0.5, 0);
    vec4 diff_ramp = texture(diffuse_ramp, diff_tex);
    vec4 diffuse = kd * Id * diff_ramp;

    float spec_calc = pow(max(dot(h, n), 0), s);
    vec2 spec_tex = vec2(spec_calc, 0);
    vec4 spec_ramp = texture(specular_ramp, spec_tex);
    vec4 specular = ks * Is * spec_ramp;

    color = ambient + diffuse + specular;
}
