//
//  "$Id: Types.h 16720 2010-12-01 09:51:53Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA3_TYPES_H__
#define __DAHUA3_TYPES_H__

#include "IntTypes.h"
////////////////////////////////////////////////////////////////////////////////

// WIN32 Dynamic Link Library
#ifdef _MSC_VER

/// ����INTERFACE_API��ʹ�ã�ÿ��ģ��DLLӦ�ö����Լ���XXX_API����ο�INFRA_API�Ķ���
#ifdef _DLL_BUILD
	#define  INTERFACE_API _declspec(dllexport)
#elif defined _DLL_USE
	#define  INTERFACE_API _declspec(dllimport)
#else
	#define INTERFACE_API
#endif

#else
	#define INTERFACE_API
#endif

#if (defined (WIN32) || defined(WIN64))
#   define CALLMETHOD __stdcall
#else
#	define CALLMETHOD
#endif // end #if (defined (WIN32) || defined(WIN64))

#ifdef __GNUC__
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

#define MAX_POLYGON_PEAK_NUM        128     ///< ������ζ������


/// IP ��ַ�ṹ
typedef union tagMvSIpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
}IpAddress;

//////////////////////////////////////////////////////////////////////////
/// ϵͳʱ�䶨��
typedef struct tagMvSSystemTime
{
	int32_t  year;		///< �ꡣ
	int32_t  month;		///< �£�January = 1, February = 2, and so on.
	int32_t  day;		///< �ա�
	int32_t  wday;		///< ���ڣ�Sunday = 0, Monday = 1, and so on
	int32_t  hour;		///< ʱ��
	int32_t  minute;	///< �֡�
	int32_t  second;	///< �롣
	int32_t  isdst;		///< ����ʱ��ʶ��
}MvSSystemTime;	



/// 2D��ṹ�嶨��
typedef struct tagMvSPoint
{
	int32_t     x;
	int32_t     y;
} MvSPoint;

typedef struct tagMvSPoint2Di32
{
	int32_t		x;
	int32_t		y;
} MvSPoint2Di32;

typedef struct tagMvSPoint2Di16
{
	int16_t		x;
	int16_t		y;
} MvSPoint2Di16;

typedef struct tagMvSPoint2Df32
{
	float		x;
	float		y;
} MvSPoint2Df32;

typedef struct tagMvSPoint2Df64
{
	double		x;
	double		y;
} MvSPoint2Df64;



/// 3D��ṹ�嶨��
typedef struct tagMvSPoint3Di32
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
} MvSPoint3Di32;

typedef struct tagMvSPoint3Di16
{
	int16_t		x;
	int16_t		y;
	int16_t		z;
} MvSPoint3Di16;

typedef struct tagMvSPoint3Df32
{
	float		x;
	float		y;
	float		z;
} MvSPoint3Df32;

typedef struct tagMvSPoint3Df64
{
	double		x;
	double		y;
	double		z;
} MvSPoint3Df64;



/// ����
typedef struct tagMvSRect
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} MvSRect;

/// �ߴ�
typedef struct tagMvSSize
{
	int32_t w;
	int32_t h;
} MvSSize;

/// ��ɫ
typedef struct tagMvSColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} MvSColor;

/// ֱ��
typedef struct tagMvSLine
{
	MvSPoint start;
	MvSPoint end;
} MvSLine;

typedef struct tagMvSLinePA
{
	MvSPoint2Df32   point;
	float           angle;
}MvSLinePA;

/// ʱ��νṹ
typedef struct tagMvSTimeSection
{
	int enable;			///< ʹ��
	int startHour;		///< ��ʼʱ��:Сʱ
	int	startMinute;	///< ��ʼʱ��:����
	int	startSecond;	///< ��ʼʱ��:����
	int	endHour;		///< ����ʱ��:Сʱ
	int	endMinute;		///< ����ʱ��:����
	int	endSecond;		///< ����ʱ��:����
}MvSTimeSection;




/// ��ά�߶��߶ζ���
//////////////////////////////////////////////////////////////////////////
typedef struct tagMvSLineSeg2Di32
{
	MvSPoint2Di32		pt1;
	MvSPoint2Di32    	pt2;
} MvSLineSeg2Di32;

typedef struct tagMvSLineSeg2Df32
{
	MvSPoint2Df32		pt1;
	MvSPoint2Df32		pt2;
} MvSLineSeg2Df32;

typedef struct tagMvSLineSegPtSlope2Df32
{
	float				angle;
	float				length;
	MvSPoint2Df32		pt;
} MvSLineSegPtSlope2Df32;

typedef union tagMvULineSeg
{
	MvSLineSeg2Df32		    twoPt;				///< ����ʽ
    MvSLineSegPtSlope2Df32	ptSlope;			///< ��бʽ
	int32_t reserved[32];
}MvULineSeg;

typedef enum TypeLineSeg
{
    LINESEG_TOW_POINT = 0,                      ///< ����ʽ
    LINESEG_POINT_SLOPE,                        ///< ��бʽ
}TypeLineSeg;

typedef struct tagMvSLineSeg
{
    TypeLineSeg         type;                   ///< �߶�����
    MvULineSeg          lineSeg;				///< �߶�
    int32_t             reserved[31];           ///< Ԥ���ֶ�
} MvSLineSeg;


//�ߴ綨��
/////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSSizei32
{
	int32_t		width;							///< ��
	int32_t		height;							///< ��
} MvSSizei32;

typedef struct tagMvSSizef32
{
	float		width;							///< ������
	float		height;
} MvSSizef32;
/////////////////////////////////////////////////////////////////////////////////////

//���ο�ṹ��
//////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSRect2Di32
{
	MvSPoint2Di32		ul;	//����
	MvSPoint2Di32		lr;	//����
} MvSRect2Di32;

typedef struct tagMvSRect2Df32
{
	MvSPoint2Df32	ul;	//����
	MvSPoint2Df32	lr;	//����
} MvSRect2Df32;

/*����*/
typedef struct tagMvSRectangle 
{
    float                   cx;         ///< ����x
    float                   cy;         ///< ����y
    float                   lx;         ///< x����
    float                   ly;         ///< y����
    float                   ra;         ///< ��ת�Ƕ�
    float                   ska;        ///< б�нǶ�
}MvSRectangle;

/*Բ*/
typedef struct tagMvSCircle
{
    float                   cx;         ///< ����x
    float                   cy;         ///< ����y
    float                   radius;     ///< �뾶
} MvSCircle;

/* Բ�� */
typedef struct tagMvSArc
{
    float                   cx;         ///< Բ������X
    float                   cy;         ///< Բ������Y
    float                   radius;     ///< Բ���뾶
    float                   angleStart; ///< ��ʼ�Ƕ�
    float                   angleSpan;  ///< �Ƕȷ�Χ
}MvSArc;


/*��Բ*/
typedef struct tagMvSEllipse
{
    float                   cx;         ///< ����x
    float                   cy;         ///< ����y
    float                   rx;         ///< x��ϵ��
    float                   ry;         ///< y��ϵ��
    float                   ra;         ///< ��ת�Ƕ�
    float                   ska;        ///< б�нǶ�
}MvSEllipse;

//Բ����
typedef struct tagMvSAnnulusSection
{
    float               cx;             ///< ����x
    float               cy;             ///< ����y
    float               innerR;         ///< ��Բ�뾶
    float               outerR;         ///< ��Բ�뾶
    float               startAngle;     ///< ��ʼ�Ƕ�
    float               endAngle;       ///< ��ֹ�Ƕ�
    int32_t             reserved[26];   ///< Ԥ���ֶ�
} MvSAnnulusSection;

//�����
typedef struct tagMvSPolygonf32
{
    int32_t             num;                            ///< ��������
    MvSPoint2Df32       pts[MAX_POLYGON_PEAK_NUM];      ///< ��������
    int32_t             reserved[31];                   ///< Ԥ���ֶ�
} MvSPolygonf32;

///32λ����128���ֽ�
typedef union tagMvUGraphObj
{
	MvSRectangle		rect;						           ///< type == 0
	MvSCircle			circle;								   ///< type == 1
	MvSEllipse			ellipse;							   ///< type == 2
    MvSPolygonf32       polygon;
    MvSAnnulusSection   annulusSection;
	int32_t reserved[32];
}MvUGraphObj;

///< ����Ŀ��
typedef struct tagMvSGraphBase
{
	int32_t				type;															///< Ŀ������
	MvUGraphObj			graph;															///< Ŀ������
}MvSGraphBase;

//////////////////////////////////////////////////////////////
/*ͼ��ṹ�嶨��*/
typedef struct tagMvSImage
{
    int32_t                 type;       //ͼ���ʽ����PublicDefine.h��MvsImgType
    int32_t                 dataType;   //�洢���ͣ���PublicDefine.h��MvsImgDataType
    int32_t                 width;      //����ͼ�����ݿ��
    int32_t                 height;     //����ͼ�����ݸ߶�
    MvSRect2Di32            roi;        //��Ч��������
    uint8_t                 *imageData; //ͼ������ָ��	
    uint8_t                 *mask;      //ͼ����Ĥ��0 (MVS_NULL)��ʾû����Ĥ
    int32_t                 *reserved[22];  // Ԥ���ֶ�1
}MvSImage;


typedef struct tagMvSLineCoef
{
	float		    a;
	float		    b;
	float		    c;
}MvSLineCoef;


/*ROI*/
typedef struct tagMvSROI
{
    int32_t							num;							//ROI����
    MvSRect2Di32					*rect;							//ROI��Ӿ���
    MvSImage						*img;							//ROIͼ��
}MvSROI;


/*coordinate struct*/
typedef struct tagMvSCoordinate
{
	float x;               // ƽ��x������
	float y;               // ƽ��y������
	float scale;           // ���ų߶�
	float ratio;           // y�ᵥλ��x�ᵥλ�ı���
	float ra;              // ��ת��
	float ska;             // ��б��
	int firstProc;        //ģ��ƥ��֮��ĵ�һ��ִ��
	int32_t *reserved[25]; // Ԥ���ֶ�1
}MvSCoordinate;

//ͼ�����Ͷ��壨����_ɨ�跽ʽ_ͼ������_����˵����
typedef enum tagMvSImgType
{
	//����ɨ��ͼ��
	/* Yƽ�汣���ʽ */
	MVS_IMGTP_UITL_Y			= 0x0100,
	/* RGBƽ�汣���ʽ */
	MVS_IMGTP_UITL_RGB			= 0x0200,
	/* RGB 24ƽ�汣���ʽ - R��һ��ƽ�棬G��һƽ�棬B��һ��ƽ�档*/
	MVS_IMGTP_UITL_RGBP_24		= 0x0201,
	/* HSI ƽ�汣���ʽ */
	MVS_IMGTP_UITL_HSI			= 0x0400,
	/* LAB ƽ�汣���ʽ */
	MVS_IMGTP_UITL_LAB			= 0x0500,
	/* LAB ƽ�汣���ʽ */
	MVS_IMGTP_UITL_DIF			= 0x0600,
	/* XYZ ƽ�汣���ʽ */
	MVS_IMGTP_UITL_XYZ			= 0x0700,
	/* UITL_YUV*/
	MVS_IMGTP_UITL_YUV			= 0x1000,
	/* YUV 420ƽ�汣���ʽ - YUV��һ��ƽ�档*/
	MVS_IMGTP_UITL_YUV_420,
	/* YUV 420ƽ�汣���ʽ - Y��һ��ƽ�棬U��һ��ƽ�棬VҲ��һ��ƽ�档*/
	MVS_IMGTP_UITL_YUVP_420,
	/* YUV 420��ƽ�汣���ʽ - Y��һ��ƽ�棬UV����һƽ�棨�����棩��*/
	MVS_IMGTP_UITL_YUVSP_420,
	/* YUV 420��ƽ�汣���ʽ - Y��һ��ƽ�棬VU����һƽ�棨�����棩��*/
	MVS_IMGTP_UITL_YVUSP_420,
	/* YUV 422ƽ�汣���ʽ - YUV��һ��ƽ�档*/
	MVS_IMGTP_UITL_YUV_422,
	/* YUV 422ƽ�汣���ʽ - Y��һ��ƽ�棬V��һ��ƽ�棬UҲ��һ��ƽ�档*/
	MVS_IMGTP_UITL_YUVP_422,
	/* YUV 422��ƽ�汣���ʽ - Y��һ��ƽ�棬UV����һƽ�棨�����棩��*/
	MVS_IMGTP_UITL_YUVSP_422,
	/* YUV 422��ƽ�汣���ʽ - Y��һ��ƽ�棬VU����һƽ�棨�����棩��*/
	MVS_IMGTP_UITL_YVUSP_422,

	//����ɨ��ͼ��
	/* ITL_YUV*/
	MVS_IMGTP_ITL_YUV			= 0x3000,
	/* YUV 420ƽ�汣���ʽ - Y��һ��ƽ�棬U��һ��ƽ�棬VҲ��һ��ƽ�档*/
	MVS_IMGTP_ITL_YUVP_420,
	/* YUV 420��ƽ�汣���ʽ - Y��һ��ƽ�棬UV����һƽ�棨�����棩��*/
	MVS_IMGTP_ITL_YUVSP_420,
	/* YUV 420��ƽ�汣���ʽ - Y��һ��ƽ�棬VU����һƽ�棨�����棩��*/
	MVS_IMGTP_ITL_YVUSP_420,
	/* YUV 422ƽ�汣���ʽ - Y��һ��ƽ�棬V��һ��ƽ�棬UҲ��һ��ƽ�档*/
	MVS_IMGTP_ITL_YUVP_422,
	/* YUV 422��ƽ�汣���ʽ - Y��һ��ƽ�棬UV����һƽ�棨�����棩��*/
	MVS_IMGTP_ITL_YUVSP_422,
	/* YUV 422��ƽ�汣���ʽ - Y��һ��ƽ�棬VU����һƽ�棨�����棩��*/
	MVS_IMGTP_ITL_YVUSP_422,
	/* �ڸ�ʽ����*/
}MvSImgType;


/*ͼ�����ݸ�ʽ*/
typedef enum tagMvSImgDataType
{
	/*�޷���8λ*/
	MVS_IMGDTP_U8			= 0,								
	/*�з���8λ*/
	MVS_IMGDTP_S8,
	/*�з���32λ*/
	MVS_IMGDTP_S32,			
	/*�޷���32λ*/
	MVS_IMGDTP_U32,			
	/*�з���16λ*/
	MVS_IMGDTP_S16,			
	/*�޷���16λ*/
	MVS_IMGDTP_U16,			
	/*����32λ*/
	MVS_IMGDTP_F32,		
	/*����64λ*/
	MVS_IMGDTP_F64,
}MvSImgDataType;

//Ŀ������
typedef enum tagMvSObjectType
{
	/*��*/
	MVS_OBJTP_POINT,
	/*�߶�*/
	MVS_OBJTP_LINE_SEG,
	/*��*/
	MVS_OBJTP_LINE,
	/*Բ*/
	MVS_OBJTP_CIRCLE,
	/*��Բ*/
	MVS_OBJTP_ELLIPSE,
	/*ͼ��*/
	MVS_OBJTP_IMG,
}MvSObjectType;

//��Ӧ�Ծ���
typedef struct tagMvSHomMat2D
{
    float mat[9];
}MvSHomMat2D;

//����
typedef struct tagMvSMat2Di32
{
	int32_t				rows;		//���������
	int32_t				cols;		//���������
	int32_t				*data;		//���������
} MvSMat2Di32;

typedef struct tagMvSMat2Df32
{
	int32_t				rows;		//���������
	int32_t				cols;		//���������
	float				*data;		//���������
}MvSMat2Df32;

typedef struct tagMvSMat2Df64
{
	int32_t				rows;		//���������
	int32_t				cols;		//���������
	double				*data;		//���������
}MvSMat2Df64;

typedef struct tagMvSRotateRect
{
	float		centerX;		//���ĵ�			
	float		centerY;
	float		hWidth;			//���ΰ�� ��
	float		hHeight;
	float		angle;			//��ת�Ƕ�
	int32_t     reserved[27];   // Ԥ���ֶ�
}MvSRotateRect;

typedef struct tagMvSRegion
{
	int32_t			imgWidth;
	int32_t			imgHeight;		//region����ͼ����
	uint32_t		area;           // ���
	MvSPoint2Df32	center;         // ����
	float			circularity;	// Բ��
	float			rectangularity;	// ���ζ�
	float			convexity;		// ͹��
	float			contlength;		// �ܳ�
	MvSRotateRect	minRect;		// ��С��Ӿ���
	int32_t			boxTop;			//��Χ����ϢX1
	int32_t			boxLeft;		//��Χ����ϢY1
	int32_t			boxRight;		//��Χ����ϢX2
	int32_t			boxDown;		//��Χ����ϢY2

	int32_t			conFlag;		//1 8��ͨ 2 ����ͨ
	uint32_t		conSize;		//������С
	uint16_t		*conAdrX;		//������ַ��������������ΪjU16
	uint16_t		*conAdrY;		//������ַ��������������ΪjU16

	int32_t			posFlag;
	uint32_t		posSize;		//�����С
	uint16_t		*areaAdrX;		//�����ַ��������������ΪjU16
	uint16_t		*areaAdrY;		//�����ַ��������������ΪjU16

	int32_t			runFlag;		// 1 8��ͨ 2 ����ͨ
	uint32_t		runNum;         // �г�����
	uint16_t		*runRow;        // �г�������
	uint16_t		*runStart;      // �г���ʼ��
	uint16_t		*runEnd;        // �г���ֹ��
	int32_t			reserved[6];    // Ԥ���ֶ�
}MvSRegion;

typedef struct tagMvSMultiRegion
{
	uint32_t areaNum;       //�������
	MvSRegion *regions;		//����
}MvSMultiRegion;

#endif// __DAHUA_TYPES_H__