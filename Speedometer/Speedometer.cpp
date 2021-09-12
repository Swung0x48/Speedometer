#include "Speedometer.h"

IMod* BMLEntry(IBML* bml) {
	return new Speedometer(bml);
}

CK3dObject* Speedometer::get_current_ball() {
	auto* current_level_array_ = m_bml->GetArrayByName("CurrentLevel");
	if (current_level_array_)
		return static_cast<CK3dObject*>(current_level_array_->GetElementObject(0, 1));

	return nullptr;
}

void Speedometer::OnLoadObject(CKSTRING filename, BOOL isMap, CKSTRING masterName, CK_CLASSID filterClass, BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic, XObjectArray* objArray, CKObject* masterObj)
{
	/*if (isMap) {
		speed_label_ = std::make_unique<BGui::Label>("L_Speedometer");
		speed_label_->SetFont(ExecuteBB::GAMEFONT_01);
		speed_label_->SetPosition(Vx2DVector(0, 0.9));
		speed_label_->SetSize(Vx2DVector(1, 0.2));
		speed_label_->SetAlignment(CKSPRITETEXT_CENTER);
		speed_label_->SetText("0.00");
		speed_label_->SetVisible(true);
	}*/
}

void Speedometer::OnStartLevel() {
	speed_label_ = std::make_unique<BGui::Label>("L_Speedometer");
	speed_label_->SetFont(ExecuteBB::GAMEFONT_01);
	speed_label_->SetPosition(Vx2DVector(0.0f, 0.9f));
	speed_label_->SetSize(Vx2DVector(1.0f, 0.0353f));
	speed_label_->SetAlignment(ALIGN_CENTER);
	speed_label_->SetText("0.00 m/s");
	speed_label_->SetVisible(true);
}

void Speedometer::OnLoad()
{

}

void Speedometer::OnProcess()
{
	if (m_bml->IsPlaying()) {
		auto* ball = get_current_ball();
		VxVector current_position;
		
		if (ball != nullptr) {
			ball->GetPosition(&current_position);
			double x_component = current_position.x - last_position_.x;
			double y_component = current_position.y - last_position_.y;
			double z_component = current_position.z - last_position_.z;

			x_component *= x_component;
			y_component *= y_component;
			z_component *= z_component;

			double distance = sqrt(x_component + y_component + z_component);
			double delta_time = m_bml->GetTimeManager()->GetLastDeltaTime();
			
			double speed = distance / delta_time * 1000;

			sprintf(display_, "%.2lf m/s", speed);
			speed_label_->SetText(display_);
			

			last_position_ = current_position;
		}
	}
	if (speed_label_ != nullptr && m_bml->IsIngame())
		speed_label_->Process();
}
