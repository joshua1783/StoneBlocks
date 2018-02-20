#ifndef SYS_FADE_H
#define SYS_FADE_H

#define SPEED 0.005;

class CFade
{
public:
	CFade();
	~CFade(){};
	static CFade* GetInstance();
	void UpData();
	void Draw();
	void FadeIn();
	void FadeOut();
	bool CheckFade();
private:
	float rate;
	bool flag_Fade;
	bool flag_FadeType;
	bool ParamChange(float);
};

#endif
