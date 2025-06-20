#pragma once
#include "GameEngine_Ver3_83.h"
#include <fstream>
#include <sstream>

//僎乕儉撪慡堟偱巊梡偡傞峔憿懱側偳傪掕媊偡傞
//-----------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------
namespace  MyPG
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//----------------------------------------------
	//僇儊儔婎杮宍
	class Camera
	{
		Camera( ){ }
		Camera(
				const ML::Vec3&		tg_,	//	旐幨懱偺埵抲
				const ML::Vec3&		pos_,	//	僇儊儔偺埵抲
				const ML::Vec3&		up_,	//	僇儊儔偺忋曽岦傪帵偡儀僋僩儖乮戝懱倄亄屌掕乯
				float				fov_,	//	帇栰妏
				float				np_,	//	慜僋儕僢僾暯柺乮偙傟傛傝慜偼塮傜側偄乯
				float				fp_,	//	屻僋儕僢僾暯柺乮偙傟傛傝屻傠偼塮傜側偄乯
				float				asp_);	//	傾僗儁僋僩斾乮夋柺偺斾棪偵崌傢偣傞丂墶亐廲乯			
	public:
	//	價儏乕忣曬乮曽岦娭楢乯
		ML::Vec3 target;			//	旐幨懱偺埵抲
		ML::Vec3 pos;			//	僇儊儔偺埵抲
		ML::Vec3 up;				//	僇儊儔偺忋曽岦傪帵偡儀僋僩儖乮戝懱倄亄屌掕乯
	//	幩塭忣曬乮帇栰斖埻娭楢乯
		float fov;					//	帇栰妏
		float nearPlane;			//	慜僋儕僢僾暯柺乮偙傟傛傝慜偼塮傜側偄乯
		float forePlane;			//	屻僋儕僢僾暯柺乮偙傟傛傝屻傠偼塮傜側偄乯
		float aspect;				//	傾僗儁僋僩斾乮夋柺偺斾棪偵崌傢偣傞丂墶亐廲乯
	//	峴楍忣曬
		ML::Mat4x4  matView, matProj;
		~Camera( );
		using SP = shared_ptr<Camera>;
	//	僇儊儔傪惗惉偡傞
		static SP Create(
				const ML::Vec3&		tg_,	//	旐幨懱偺埵抲
				const ML::Vec3&		pos_,	//	僇儊儔偺埵抲
				const ML::Vec3&		up_,	//	僇儊儔偺忋曽岦傪帵偡儀僋僩儖乮戝懱倄亄屌掕乯
				float				fov_,	//	帇栰妏
				float				np_,	//	慜僋儕僢僾暯柺乮偙傟傛傝慜偼塮傜側偄乯
				float				fp_,	//	屻僋儕僢僾暯柺乮偙傟傛傝屻傠偼塮傜側偄乯
				float				asp_);	//	傾僗儁僋僩斾乮夋柺偺斾棪偵崌傢偣傞丂墶亐廲乯	
	//	僇儊儔偺愝掕
		void UpDate( );
	};
	//----------------------------------------------
	class MyGameEngine : public GameEngine
	{
	public:
		MyGameEngine( );
	//僎乕儉僄儞僕儞偵捛壛偟偨傕偺偺弶婜壔偲奐曻
		bool Initialize(HWND wnd_);
		~MyGameEngine( );
	//僎乕儉僄儞僕儞偵捛壛偟偨傕偺偺僗僥僢僾張棟
		void UpDate( );

	//3DPG1懳墳偵傛傝捛壛
		//2D昤夋娐嫬偺僨僼僅儖僩僷儔儊乕僞愝掕
		void Set2DRenderState(DWORD l_);
		//3D昤夋娐嫬偺僨僼僅儖僩僷儔儊乕僞愝掕
		void Set3DRenderState(DWORD l_);

	//僎乕儉僄儞僕儞偵捛壛偟偨偄傕偺偼壓偵壛偊傞
	//----------------------------------------------
		MyPG::Camera::SP		camera[4];		//	僇儊儔


		XI::Mouse::SP  mouse;
		XI::GamePad::SP  in1, in2, in3, in4;	//庢傝崌偊偢係杮
	//----------------------------------------------
	};
}
extern MyPG::MyGameEngine* ge;


