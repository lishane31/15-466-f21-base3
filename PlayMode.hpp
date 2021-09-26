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

	float time = 0.0f;
	int repeat_rate = 14;

	std::string text = "Students at Carnegie Mellon are engaged in intellectual activity consistent with the highest standards of the academy. The relationship between students and instructors and their shared commitment to overarching standards of respect, honor and transparency determine the integrity of our community of scholars. The actions of our students, faculty and staff are a representation of our university community and of the professional and personal communities that we lead. Therefore, a deep and abiding commitment to academic integrity is fundamental to a Carnegie Mellon education. Honesty and good faith, clarity in the communication of core values, professional conduct of work, mutual trust and respect, and fairness and exemplary behavior represent the expectations for ethical behavior for all members of the Carnegie Mellon community.";
	int index = 0;
	std::string curr = "";
};
