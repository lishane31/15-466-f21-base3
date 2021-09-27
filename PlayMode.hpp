#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		bool down = false;
		bool pressed = false;
	} a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;

	//std::vector< Button > buttons = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	// //hexapod leg to wobble:
	// Scene::Transform *hip = nullptr;
	// Scene::Transform *upper_leg = nullptr;
	// Scene::Transform *lower_leg = nullptr;
	// glm::quat hip_base_rotation;
	// glm::quat upper_leg_base_rotation;
	// glm::quat lower_leg_base_rotation;
	// float wobble = 0.0f;

	glm::vec3 get_leg_tip_position();

	//music coming from the tip of the leg (as a demonstration):
	std::shared_ptr< Sound::PlayingSample > leg_tip_loop;
	
	//camera:
	Scene::Camera *camera = nullptr;

	float time = 13.75f;
	int repeat_rate = 16;

	std::string text = 	"Students at Carnegie Mellon are engaged in intellectual activity consistent with the highest "
						"standards of the academy. The relationship between students and instructors and their shared "
						"commitment to overarching standards of respect, honor and transparency determine the integrity "
						"of our community of scholars.";

	//https://www.beepbox.co/#8n31sbk0l00e03t2mm0a7g0fj07i0r1o3210T1v1L4u27q1d1f9y0z7C0c0A0F2B6V7Q4190Pf640E0111T5v1L4u28q1d5f9y1z7C1c0h8H_--D---ZBLRS-ST1v1L4u34q1d5f7y1z7C0c0AcFhB3V6Q01a5P9939E0000T2v1L4u15q0d1f8y0z1C2w0b4zg0000000000000000000000000000000000000000p21dFEYczy6oGyeELF8WqGGaF7ihQRl4thvihQRlkqGi-CyhFFFFpILBkLFE-aqqqaGqidCUfCyY00000
	//https://www.beepbox.co/#8n31sbk0l00e03t2mm0a7g0fj07i0r1o3210T1v1L4u27q1d1f9y0z7C0c0A0F2B6V7Q4190Pf640E0111T5v1L4u28q1d5f9y1z7C1c0h8H_--D---ZBLRS-ST1v1L4u34q1d5f7y1z7C0c0AcFhB3V6Q01a5P9939E0000T2v1L4u15q0d1f8y0z1C2w0b4zgid18Q4zg00000000000000000000000000000000p21dFEYczy6oGyeELF8WqGGaF7ihQRl4thvihQRlkqGi-CyhFFFFpILBkLFE-aqqqaGqidCUfCyY00000
	//https://www.beepbox.co/#8n31sbk0l00e03t1Um0a7g0fj07i0r1o3210T1v1L4u27q1d1f9y0z7C0c0A0F2B6V7Q4190Pf640E0111T5v1L4u28q1d5f9y1z7C1c0h8H_--D---ZBLRS-ST1v1L4u34q1d5f7y1z7C0c0AcFhB3V6Q01a5P9939E0000T2v1L4u15q0d1f8y0z1C2w0b4zgid18Q4zg00000000000000000000000000000000p214FEYcLAqjnEbWqq2ehQ5Zd9HQ5Zdd4zEdu78W2exCOY5kLFE-2ewLG8W2dCUfGyY00000
	int index = 0, row = 0, total = 0;
	std::vector< std::string > curr;

	bool punched = false;
	float punch_timer = 0.0f;

	bool init = true;
	glm::vec3 left_pos;
	glm::vec3 right_pos;
	glm::quat left_quat;
	glm::quat right_quat;
};
