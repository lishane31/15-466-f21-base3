#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#include <random>

using namespace std;

GLuint meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("city.pnct"));
	meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > hexapod_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("city.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		// if(mesh_name.compare("Left 2") == 0){
		// 	scene.left_2 = (int)scene.drawables.size();
		// 	return;
		// } else if (mesh_name.compare("Right 2") == 0) {
		// 	scene.right_2 = (int)scene.drawables.size();
		// 	return;
		// } else if (mesh_name.compare("Left 1") == 0) {
		// 	scene.left_1 = (int)scene.drawables.size();
			
		// } else if (mesh_name.compare("Right 1") == 0) {
		// 	scene.right_1 = (int)scene.drawables.size();
		// }

		Mesh const &mesh = hexapod_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

Load< Sound::Sample > background_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("removed.wav"));
});

Load< Sound::Sample > e_note(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("e.wav"));
});

PlayMode::PlayMode() : scene(*hexapod_scene) {
	curr.emplace_back("");

	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();
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

	//There has got to be a better way of doing this...
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
		else if (evt.key.keysym.sym == SDLK_f) 	return set_pressed(f);
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
		else if (evt.key.keysym.sym == SDLK_f) 	return set_unpressed(f);
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
	if(init) {
		auto iter = scene.drawables.end();
		iter--;

		left_pos = iter->transform->position;
		left_quat = iter->transform->rotation;

		iter--;

		right_pos = iter->transform->position;
		right_quat = iter->transform->rotation;

		scene.drawables.pop_back();
		scene.drawables.pop_back();

		init = false;
	}

	time += elapsed;
	if(time >= repeat_rate) {
		time = 0;
		Sound::play(*background_sample);
	}

	//Punch for 0.2 seconds if the right letter is pressed
	punch_timer -= elapsed;
	if(punch_timer < 0) {
		punched = false;
	}

	

	auto check_letter = [this](Button &button, char letter) {
		if(button.down && !button.pressed && letter == tolower(text.at(total))) {
			Sound::play(*e_note);
			
			punched = true;
			punch_timer = 0.2f;

			curr[row] += text.at(total);
			button.pressed = true;

			total = (total + 1) % text.size();
			index++;

			//Skip all spaces and punctuations because encoding them the lazy way
			//I have been doing is very painful and idk how to make it better :'(
			while(!isalpha(text.at(total))) {
				curr[row] += text.at(total);
				
				total = (total + 1) % text.size();
				index++;

				//Go to new line if this one is too long
				if(index >= 70) {
					row++;
					index = 0;
					curr.emplace_back("");
				}
			}
		}

		button.down = false;
	};

	//Play on the high note
	if(
		abs(time - 0.5f) < 0.01f ||
		abs(time - 1.5f) < 0.01f ||
		abs(time - 2.75f) < 0.01f ||
		abs(time - 3.75f) < 0.01f ||
		abs(time - 4.75f) < 0.01f ||
		abs(time - 5.75f) < 0.01f ||
		abs(time - 7.0f) < 0.01f ||
		abs(time - 8.0f) < 0.01f ||
		abs(time - 9.0f) < 0.01f ||
		abs(time - 9.25f) < 0.01f ||
		abs(time - 9.75f) < 0.01f ||
		abs(time - 10.25f) < 0.01f ||
		abs(time - 12.25f) < 0.01f ||
		abs(time - 12.75f) < 0.01f ||
		abs(time - 13.0f) < 0.01f ||
		abs(time - 13.5f) < 0.01f
	) {
		//There has got to be a better way of doing this...
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

	//Change the characters based on whether a note was hit
	{
		Scene::Transform* left_transform = new Scene::Transform();
		left_transform->position = left_pos;
		left_transform->rotation = left_quat;

		Scene::Transform* right_transform = new Scene::Transform();
		right_transform->position = right_pos;
		right_transform->rotation = right_quat;

		scene.drawables.pop_back();
		scene.drawables.pop_back();
		
		if(!punched) {
			Mesh const &left_mesh = hexapod_meshes->lookup("Left 1");
			left_transform->name = "Left 1";

			Mesh const &right_mesh = hexapod_meshes->lookup("Right 1");
			right_transform->name = "Right 1";

			scene.drawables.emplace_back(left_transform);
			Scene::Drawable &drawable = scene.drawables.back();

			drawable.pipeline = lit_color_texture_program_pipeline;

			drawable.pipeline.vao = meshes_for_lit_color_texture_program;
			drawable.pipeline.type = left_mesh.type;
			drawable.pipeline.start = left_mesh.start;
			drawable.pipeline.count = left_mesh.count;

			scene.drawables.emplace_back(right_transform);
			Scene::Drawable &right_drawable = scene.drawables.back();

			right_drawable.pipeline = lit_color_texture_program_pipeline;

			right_drawable.pipeline.vao = meshes_for_lit_color_texture_program;
			right_drawable.pipeline.type = right_mesh.type;
			right_drawable.pipeline.start = right_mesh.start;
			right_drawable.pipeline.count = right_mesh.count;
		}
		else {
			Mesh const &left_mesh = hexapod_meshes->lookup("Left 2");
			left_transform->name = "Left 2";

			Mesh const &right_mesh = hexapod_meshes->lookup("Right 2");
			right_transform->name = "Right 2";

			scene.drawables.emplace_back(left_transform);
			Scene::Drawable &drawable = scene.drawables.back();

			drawable.pipeline = lit_color_texture_program_pipeline;

			drawable.pipeline.vao = meshes_for_lit_color_texture_program;
			drawable.pipeline.type = left_mesh.type;
			drawable.pipeline.start = left_mesh.start;
			drawable.pipeline.count = left_mesh.count;

			scene.drawables.emplace_back(right_transform);
			Scene::Drawable &right_drawable = scene.drawables.back();

			right_drawable.pipeline = lit_color_texture_program_pipeline;

			right_drawable.pipeline.vao = meshes_for_lit_color_texture_program;
			right_drawable.pipeline.type = right_mesh.type;
			right_drawable.pipeline.start = right_mesh.start;
			right_drawable.pipeline.count = right_mesh.count;
		}
	}
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
		float ofs = 2.0f / drawable_size.y;

		for(int i = 0; i <= row; i++) {
			lines.draw_text(curr[i],
				glm::vec3(-aspect + 0.1f * H, -0.6f - 0.1f*i + 0.1f * H, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0x00, 0x00, 0x00, 0x00));
			lines.draw_text(curr[i],
				glm::vec3(-aspect + 0.1f * H + ofs, -0.6f - 0.1f*i + 0.1f * H + ofs, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0xff, 0xff, 0xff, 0x00));
		}
		
		std::string next_letter = "Next letters: ";
		next_letter.append(text.substr(total, 10));

		lines.draw_text(next_letter,
			glm::vec3(-aspect + 0.5f + 0.1f * H, -0.5f + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0x00, 0x00, 0x00));

		lines.draw_text(next_letter,
			glm::vec3(-aspect + 0.5f + 0.1f * H + ofs, -0.5f + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));

		//Prompt only when you're supposed to play
		if(
			abs(time - 0.5f) < 0.1f ||
			abs(time - 1.5f) < 0.1f ||
			abs(time - 2.75f) < 0.1f ||
			abs(time - 3.75f) < 0.1f ||
			abs(time - 4.75f) < 0.1f ||
			abs(time - 5.75f) < 0.1f ||
			abs(time - 7.0f) < 0.1f ||
			abs(time - 8.0f) < 0.1f ||
			abs(time - 9.0f) < 0.1f ||
			abs(time - 9.25f) < 0.1f ||
			abs(time - 9.75f) < 0.1f ||
			abs(time - 10.25f) < 0.1f ||
			abs(time - 12.25f) < 0.1f ||
			abs(time - 12.75f) < 0.1f ||
			abs(time - 13.0f) < 0.1f ||
			abs(time - 13.5f) < 0.1f
		) {
			lines.draw_text("Play",
				glm::vec3(-aspect + 2.0f + 0.1f * H, -0.5f + 0.1f * H, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0xff, 0x00, 0x00, 0x00));

			lines.draw_text("Play",
				glm::vec3(-aspect + 2.0f + 0.1f * H + ofs, -0.5f + 0.1f * H + ofs, 0.0),
				glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
				glm::u8vec4(0xff, 0xff, 0xff, 0x00));
		}

	}
	GL_ERRORS();
}

glm::vec3 PlayMode::get_leg_tip_position() {
	//the vertex position here was read from the model in blender:
	return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
