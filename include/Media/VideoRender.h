/**
* @file   VideoRender.h
* @brief  ��ʾ�⣬��YUV��ʾ��ͼ��.
* @author 
* @par    Copyright (c):
*         All Rights Reserved
* @date   2015-08-17
* @note   �ӿ����̲߳���ȫ�ġ�
* @version 1.00.1
*/
#ifndef __VIDEORENDER_H_
#define __VIDEORENDER_H_

#ifdef  __cplusplus
extern "C"{
#endif  // end #ifdef  __cplusplus

#ifdef WIN64
#undef WIN32
#endif

/** ����ѡ�� */
#ifdef WIN32  // win64λ�£��ᱨ��def�ظ�����ľ���
#  ifdef _USRDLL // ��̬�⵼��
#    ifdef VIDEORENDER_EXPORTS
#		define VRENDER_API __declspec(dllexport)
#	 else
#		define VRENDER_API __declspec(dllimport)
#	 endif
#  else
#    define VRENDER_API
#endif 
#else
#	define VRENDER_API
#endif //end #ifdef WIN32


#if (defined (WIN32) || defined(WIN64))
#   define CALLMETHOD __stdcall
#	define CALLBACK	__stdcall
#else
#	define CALLMETHOD
#	define CALLBACK
#endif // end #if (defined (WIN32) || defined(WIN64))

#define IN
#define OUT

typedef void* VR_HANDLE;     /**< ����APIʹ�õľ�� */
typedef void* VR_HWND;       /**< ���ھ�� */
typedef void* VR_HDC;        /**< ��ͼ��� */
typedef void* VR_HFONT;      /**< ������ */

/**
* @enum tagRenderMode
* @brief ��Ƶ��ʾģʽö�ٶ���
* @attention ��
*/
typedef enum tagVideoRenderMode
{
#if (defined (WIN32) || defined(WIN64))
	VR_MODE_D3D = 0,             /**< ʹ��D3D�ķ�ʽ������ʾ */
	VR_MODE_GDI,                 /**< ʹ��GDI��ʾģʽ */
#else
	VR_MODE_OPENGLX,			 /**< ʹ��Opengl�ķ�ʽ������ʾ */
	VR_MODE_X11,				 /**< ʹ��X11�ķ�ʽ������ʾ */
#endif // end #if (defined (WIN32) || defined(WIN64))
}VR_MODE_E;

/**
* @enum tagVideoRenderErr
* @brief �ӿڷ���ֵ
* @attention ��
*/
typedef enum tagVideoRenderErr
{
	VR_SUCCESS,
	VR_ILLEGAL_PARAM,			 /**< �Ƿ�����*/
	VR_ERR_ORDER,                /**< ���ýӿ�˳�����*/
	VR_NO_MEMORY,				 /**< �ڴ治��*/
	VR_NOT_SUPPORT,              /**< ��֧�֣�����ȱ��ϵͳ�⣬���ǲ�֧������Ĳ���ֵ*/
	VR_D3D_PRESENT_FAILED,       /**< D3D��ʾ���� */
	VR_GDI_CREATE_OBJ_FAILED,    /**< GGI��������ʧ�� */
	VR_DEFAULT_FONT_NOT_EXIST,   /**< Ĭ�����岻���� */
}VR_ERR_E;

/**
* @enum tagVideoRenderPixelType
* @brief ֡��������
* @attention ��
*/
typedef enum tagVideoRenderPixelType
{
	VR_PIXEL_FMT_NONE = -1,
	VR_PIXEL_FMT_YUV420P,				    ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	VR_PIXEL_FMT_RGB24,                     ///< packet RGB 8:8:8, 24bpp, RGBRGB...
	VR_PIXEL_FMT_MONO8,						///< mono8
	
}VR_PIXEL_TYPE_E;

/**
* @struct tagVideoRenderOpenParam
* @brief ����Ƶ��ʾ����Ҫ�Ĳ�������VR_Open�ӿ�ʹ�á�
* @attention ��
*/
typedef struct tagVideoRenderOpenParam
{
	VR_HWND hWnd;				/**< ���ھ��*/
	VR_MODE_E eVideoRenderMode; /**< ��ʾģʽ*/
	int nWidth;					/**< ��Ƶ��*/
	int nHeight;				/**< ��Ƶ��*/
}VR_OPEN_PARAM_S;

/**
* @struct tagVideoRenderFrame
* @brief ��ʾ��Ƶ����Ҫ�Ĳ�������VR_RenderFrame�ӿ�ʹ�á�
* @attention ��
*/
typedef struct tagVideoRenderFrame
{
#define NUM_DATA_POINTS 4
	unsigned char* data[NUM_DATA_POINTS];      /**< ����format������YUV420Pʱÿ�������ֱ��ʾָ��Y��U��V���壬RGBʱ��ֻʹ��data[0]��ָ��RGB����*/
	int stride[NUM_DATA_POINTS];			   /**< ÿ�������Ŀ��*/
	int nWidth;								   /**< ��Ƶ��,Ϊ�˷�ֹ��ʾ�������޸ķֱ���*/
	int nHeight;							   /**< ��Ƶ��,Ϊ�˷�ֹ��ʾ�������޸ķֱ���*/
	VR_PIXEL_TYPE_E format;
}VR_FRAME_S;


/**
* @struct tagVideoRenderRenderParam
* @brief ��ʾ��Ƶ����Ҫ�Ĳ�������VR_RenderEx�ӿ�ʹ�á�
* @attention ������ʹ��,�����ϰ汾������
*/
typedef struct tagVideoRenderRenderParam
{
	unsigned char* data[3];    /**< ÿ�������ֱ��ʾָ��Y��U��V����*/
	int stride[3];			   /**< ÿ�������Ŀ��*/
	int nWidth[3];			   /**< ÿ�������Ŀ�*/
	int nHeight[3];			   /**< ÿ�������ĸ�*/
}VR_RENDER_PARAM_S;

#if (defined(WIN32) || defined (WIN64))
typedef COLORREF VR_COLOR;
#else
typedef unsigned int VR_COLOR;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb)>>16))
#define RGB(r,g,b) ((VR_COLOR)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/**
* @struct tagFontInfo
* @brief �����������VR_CreateFont�ӿ�ʹ�á�
* @attention ��
*/
typedef struct tagFontInfo
{
	unsigned int nFontSize;    ///< �����С
}VR_FONT_INFO;

/**
* @struct tagVRPoint
* @brief ������
* @attention ��
*/
typedef struct tagVRPoint {
   long x;
   long y;
} VR_POINT;

/**
* @struct tagVRRect
* @brief ����
* @attention ��
*/
typedef struct tagVRRect
{
	int    left;
	int    top;
	int    right;
	int    bottom;
}VR_RECT;

/**
*  @brief  ����һ�����Ŷ���
*  @param[in]  pParam��VR_OPEN_PARAM_S�ṹ�塣���ɲ��Ŷ�������Ҫ�Ĳ�����
*  @param[out] pHandle��VR_HANDLE�����������ɵĲ��ŵĶ���
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note   ִ�гɹ�����Ҫ����VR_Close���ͷ���Դ��
*  @see    VR_ERR_E��VR_Close
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_Open(IN VR_OPEN_PARAM_S* pParam, OUT VR_HANDLE* pHandle);

/**
*  @brief  �������һ֡YUV��ʾ��ͼ��
*  @param[in] handle��VR_HANDLE�������VR_Open������
*  @param[in] param��VR_FRAME_S�ṹ�塣
*  @param[in] pEnlargeRect��VR_RECT�ṹ�塣�Ŵ��������ԭͼ��С��ʾ������Ҫ�Ŵ�ʱ����NULL��
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note   ����һ֡����ʾ�������ٶ����ⲿ�����ٶȿ��ơ�
*  @see    VR_ERR_E
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_RenderFrame(IN VR_HANDLE handle, IN VR_FRAME_S* param, IN VR_RECT* pEnlargeRect);


/**
*  @brief  �رղ��Ŷ���
*  @param[in] handle��VR_HANDLE�������VR_Open������
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note   ��VR_Open���ʹ�á�
*  @see    VR_ERR_E��VR_Open
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_Close(IN VR_HANDLE handle);


typedef void (CALLBACK *fnDrawCallback)(VR_HWND hWindow, VR_HDC hDrawHandle, void* pUserData);
/**
*  @brief  ����GDI�ص�, ����ʹ��GDI�ڻ����л��Ƶ�����ʾ
*  @param[in] handle��VR_HANDLE�������VR_Open������
*  @param[in] callback���ص�����
*  @param[in] pUserData���û��ص�����
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_SetDrawCallback(IN VR_HANDLE handle, IN fnDrawCallback callback, IN void* pUserData);


/**
*  @brief ����������
*  @param[in] pFontInfo��������Ϣ��������ɫ�������С��
*  @param[out] hFont�����������
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note ��ͼ����������
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_CreateFont(IN VR_FONT_INFO* pFontInfo, OUT VR_HFONT* hFont);

/**
*  @brief ����������
*  @param[in] hFont������������VR_CreateFont����
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note ��ͼ����������
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_DestroyFont(IN VR_HFONT hFont);

/**
*  @brief ���֡�֧��\n���س���ʾ
*  @param[in] hFont�����塣
*  @param[in] hWindow�����ھ������fnDrawCallback��ͼ�ص����
*  @param[in] hDrawHandle:��ͼ�������fnDrawCallback��ͼ�ص����
*  @param[in] lpText:UNICODE���뻺��ָ�룬֧��������ʾ��
*  @param[in] nTextLen:UNICODE���뻺���С
*  @param[in] color:������ɫ
*  @param[in] pointStart:��ʼ�����ַ�����λ��
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note ��ͼ����������
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_DrawText(IN VR_HFONT hFont, 
										IN VR_HWND hWindow, 
										IN VR_HDC hDrawHandle, 
										IN const char* lpText, 
										IN int nTextLen, 
										IN VR_COLOR color,
										IN VR_POINT* pointStart);



/**
*  @brief  �������һ֡YUV��ʾ��ͼ��
*  @param[in] handle��VR_HANDLE�������VR_Open������
*  @param[in] param��VR_RENDER_PARAM_S�ṹ�塣��ʾ����Ҫ�Ĳ�����
*  @param[in] pEnlargeRect��VR_RECT�ṹ�塣�Ŵ��������ԭͼ��С��ʾ������Ҫ�Ŵ�ʱ����NULL��
*  @attention �˽ӿڲ�����ʹ�ã�����ʹ��VR_RenderFrame�����Ϊ�����ϰ汾��ʹ�ö�������
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @note   ����һ֡����ʾ�������ٶ����ⲿ�����ٶȿ��ơ�
*  @see    VR_ERR_E
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_RenderEx(IN VR_HANDLE handle, IN VR_RENDER_PARAM_S* param, IN VR_RECT* pEnlargeRect);

/**
*  @brief  �������һ֡YUV��ʾ��ͼ��
*  @param[in] handle��VR_HANDLE�������VR_Open������
*  @param[in] param��VR_RENDER_PARAM_S�ṹ�塣��ʾ����Ҫ�Ĳ�����
*  @Return:    VR_ERR_E:���Žӿڷ���ֵ
*  - VR_SUCCESS ��ʾִ�гɹ�
*  - ����ֵ�� VR_ERR_Eö��
*
*  @attention �˽ӿڲ�����ʹ�ã�����ʹ��VR_RenderFrame�����Ϊ�����ϰ汾��ʹ�ö�������
*  @note   ����һ֡����ʾ�������ٶ����ⲿ�����ٶȿ��ơ�
*  @see    VR_ERR_E
*/
VRENDER_API VR_ERR_E CALLMETHOD VR_Render(IN VR_HANDLE handle, IN VR_RENDER_PARAM_S* param);

#ifdef  __cplusplus
}
#endif // end #ifdef  __cplusplus

#endif // end #ifndef __VIDEORENDER_H_
