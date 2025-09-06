#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"
#include "/home/codeleaded/System/Static/Library/Video.h"


RLCamera rlc;
Video video;
int Mode;

void Setup(AlxWindow* w){
    rlc = RLCamera_New(RLCAMERA_DEVICE,RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);
    video = Video_New(RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2,20);
    Mode = 0;
}

void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_E).PRESSED) Video_Restart(&video);
    if(Stroke(ALX_KEY_R).PRESSED) Video_Start(&video);
    if(Stroke(ALX_KEY_T).PRESSED) Video_Stop(&video);
    if(Stroke(ALX_KEY_Z).PRESSED) Video_Save(&video,"./data/Video.alxvf");
    if(Stroke(ALX_KEY_U).PRESSED){
        Video_Free(&video);
        video = Video_Load("./data/Video.alxvf");
    }
    if(Stroke(ALX_KEY_W).PRESSED) Mode = Mode < 2 ? Mode + 1 : 0;

    Clear(BLACK);

    if(Mode==0){
        Sprite sp = Sprite_None();
        int width = 0,height = 0;
        sp.img = RLCamera_Get(&rlc,&width,&height);
        sp.w = width;
        sp.h = height;

        if(sp.img){
            Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
            Sprite_Free(&sp);
        }
    }else if(Mode==1){
        Sprite sp = Sprite_None();
        int width = 0,height = 0;
        sp.img = RLCamera_Get(&rlc,&width,&height);
        sp.w = width;
        sp.h = height;

        if(sp.img){
            Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
            Video_Push(&video,sp.w * sp.h,sp.img,0.0f);
            Sprite_Free(&sp);
        }
    }else if(Mode==2){
        Video_NextImage(&video);
        Sprite_Render(WINDOW_STD_ARGS,&video.lastImage,0.0f,0.0f);
    }

    String str = String_Format("Mode: %d, Frames: %d, Frame: %d, Lasttime: %d",Mode,video.frames.size,(int)video.lastFrame,video.lastTime / TIME_NANOTOSEC);
	CStr_RenderSizeAlxFont(WINDOW_STD_ARGS,&window.AlxFont,str.Memory,str.size,0.0f,0.0f,RED);
	String_Free(&str);
}

void Delete(AlxWindow* w){
    RLCamera_Free(&rlc);
    Video_Free(&video);
}

int main(){
    if(Create("Camera VideoEncoding",1400,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}