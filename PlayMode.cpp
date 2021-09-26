#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <random>

using namespace std;

GLuint hexapod_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("city.pnct"));
	hexapod_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > hexapod_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("city.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = hexapod_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = hexapod_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

Load< Sound::Sample > background_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("song.wav"));
});

PlayMode::PlayMode() : scene(*hexapod_scene) {
	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();

	//start music loop playing:
	// (note: position will be over-ridden in update())
	Sound::play(*background_sample);
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {
	auto set_pressed = [](Button &button) {
		button.down = true;
		return true;
	};

	auto set_unpressed = [](Button &button) {
		button.pressed = false;
		return true;
	};

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_ESCAPE) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			return true;
		} 
		else if (evt.key.keysym.sym == SDLK_a) 	return set_pressed(a);
		else if (evt.key.keysym.sym == SDLK_b) 	return set_pressed(b);
		else if (evt.key.keysym.sym == SDLK_c) 	return set_pressed(c);
		else if (evt.key.keysym.sym == SDLK_d) 	return set_pressed(d);
		else if (evt.key.keysym.sym == SDLK_e) 	return set_pressed(e);
		else if (evt.key.keysym.sym == SDLK_e) 	return set_pressed(f);
		else if (evt.key.keysym.sym == SDLK_g) 	return set_pressed(g);
		else if (evt.key.keysym.sym == SDLK_h) 	return set_pressed(h);
		else if (evt.key.keysym.sym == SDLK_i) 	return set_pressed(i);
		else if (evt.key.keysym.sym == SDLK_j) 	return set_pressed(j);
		else if (evt.key.keysym.sym == SDLK_k) 	return set_pressed(k);
		else if (evt.key.keysym.sym == SDLK_l) 	return set_pressed(l);
		else if (evt.key.keysym.sym == SDLK_m) 	return set_pressed(m);
		else if (evt.key.keysym.sym == SDLK_n) 	return set_pressed(n);
		else if (evt.key.keysym.sym == SDLK_o) 	return set_pressed(o);
		else if (evt.key.keysym.sym == SDLK_p) 	return set_pressed(p);
		else if (evt.key.keysym.sym == SDLK_q) 	return set_pressed(q);
		else if (evt.key.keysym.sym == SDLK_r) 	return set_pressed(r);
		else if (evt.key.keysym.sym == SDLK_s) 	return set_pressed(s);
		else if (evt.key.keysym.sym == SDLK_t) 	return set_pressed(t);
		else if (evt.key.keysym.sym == SDLK_u) 	return set_pressed(u);
		else if (evt.key.keysym.sym == SDLK_v) 	return set_pressed(v);
		else if (evt.key.keysym.sym == SDLK_w) 	return set_pressed(w);
		else if (evt.key.keysym.sym == SDLK_x) 	return set_pressed(x);
		else if (evt.key.keysym.sym == SDLK_y) 	return set_pressed(y);
		else if (evt.key.keysym.sym == SDLK_z) 	return set_pressed(z);
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_a) 		return set_unpressed(a);
		else if (evt.key.keysym.sym == SDLK_b) 	return set_unpressed(b);
		else if (evt.key.keysym.sym == SDLK_c) 	return set_unpressed(c);
		else if (evt.key.keysym.sym == SDLK_d) 	return set_unpressed(d);
		else if (evt.key.keysym.sym == SDLK_e) 	return set_unpressed(e);
		else if (evt.key.keysym.sym == SDLK_e) 	return set_unpressed(f);
		else if (evt.key.keysym.sym == SDLK_g) 	return set_unpressed(g);
		else if (evt.key.keysym.sym == SDLK_h) 	return set_unpressed(h);
		else if (evt.key.keysym.sym == SDLK_i) 	return set_unpressed(i);
		else if (evt.key.keysym.sym == SDLK_j) 	return set_unpressed(j);
		else if (evt.key.keysym.sym == SDLK_k) 	return set_unpressed(k);
		else if (evt.key.keysym.sym == SDLK_l) 	return set_unpressed(l);
		else if (evt.key.keysym.sym == SDLK_m) 	return set_unpressed(m);
		else if (evt.key.keysym.sym == SDLK_n) 	return set_unpressed(n);
		else if (evt.key.keysym.sym == SDLK_o) 	return set_unpressed(o);
		else if (evt.key.keysym.sym == SDLK_p) 	return set_unpressed(p);
		else if (evt.key.keysym.sym == SDLK_q) 	return set_unpressed(q);
		else if (evt.key.keysym.sym == SDLK_r) 	return set_unpressed(r);
		else if (evt.key.keysym.sym == SDLK_s) 	return set_unpressed(s);
		else if (evt.key.keysym.sym == SDLK_t) 	return set_unpressed(t);
		else if (evt.key.keysym.sym == SDLK_u) 	return set_unpressed(u);
		else if (evt.key.keysym.sym == SDLK_v) 	return set_unpressed(v);
		else if (evt.key.keysym.sym == SDLK_w) 	return set_unpressed(w);
		else if (evt.key.keysym.sym == SDLK_x) 	return set_unpressed(x);
		else if (evt.key.keysym.sym == SDLK_y) 	return set_unpressed(y);
		else if (evt.key.keysym.sym == SDLK_z) 	return set_unpressed(z);
	} else if (evt.type == SDL_MOUSEBUTTONDOWN) {
		if (SDL_GetRelativeMouseMode() == SDL_FALSE) {
			SDL_SetRelativeMouseMode(SDL_TRUE);
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	time += elapsed;
	if(time >= repeat_rate) {
		time = 0;
	}

	auto check_letter = [this](Button &button, char letter) {
		if(button.down && !button.pressed && letter == tolower(text.at(index))) {		
			button.pressed = true;

			//Skip all spaces and punctuations because encoding them the lazy way
			//I have been doing is very painful and idk how to make it better :'(
			while(!isalpha(text.at(index))) {
				curr += text.at(index++);
			}
		}

		button.down = false;
	};

	check_letter(a, 'a');
	check_letter(b, 'b');
	check_letter(c, 'c');
	check_letter(d, 'd');
	check_letter(e, 'e');
	check_letter(f, 'f');
	check_letter(g, 'g');
	check_letter(h, 'h');
	check_letter(i, 'i');
	check_letter(j, 'j');
	check_letter(k, 'k');
	check_letter(l, 'l');
	check_letter(m, 'm');
	check_letter(n, 'n');
	check_letter(o, 'o');
	check_letter(p, 'p');
	check_letter(q, 'q');
	check_letter(r, 'r');
	check_letter(s, 's');
	check_letter(t, 't');
	check_letter(u, 'u');
	check_letter(v, 'v');
	check_letter(w, 'w');
	check_letter(x, 'x');
	check_letter(y, 'y');
	check_letter(z, 'z');
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		constexpr float H = 0.09f;
		lines.draw_text(curr,
			glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text(curr,
			glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
	}
	GL_ERRORS();
}

glm::vec3 PlayMode::get_leg_tip_position() {
	//the vertex position here was read from the model in blender:
	return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
