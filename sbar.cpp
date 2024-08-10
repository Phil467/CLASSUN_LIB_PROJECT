#include "sbar.h"
extern csCNTR_VARS cv;
extern HINSTANCE*Hinst;
extern csCONTAINER csc;
csSBAR::csSBAR(csCNTR_PARAMS& cscp, int idp, csRGBA bkgcol, RECT geometry, bool orient)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    if(orient==0)
    {
        cscp.DCSizes = {1400,(unsigned int)geometry.bottom};
    }
    else
    {
        cscp.DCSizes = {(unsigned int)geometry.right,1000};
    }
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=5;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=0;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.05;//zzzzzzzzzzzzzzzzzzzzzzzzzzz
    cscp.DCSizes = {1366,30};
    cscp.MinTrackSize= {1,1};
    cscp.MaxTrackSize= {1366,1000};
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= bkgcol;
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text = "";
    cscp.GeometryLink.TopLinkEvent_target = GLINK_POSITION;
    cscp.GeometryLink.TopLinkEvent_source = GLINK_SIZE;
    cscp.GeometryLink.idhwndTop = idp;
    cscp.GeometryLink.RightLinkEvent_target = GLINK_SIZE;
    cscp.GeometryLink.RightLinkEvent_source = GLINK_SIZE;
    cscp.GeometryLink.idhwndRight = idp;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {30,40,40};
    cscp.MHGradient.Color2 = bkgcol;
    cscp.MouseHoverTime = 3;
    cscp.AutoTransform.Type = AUTO_TRANSF_LENGTH;
    cscp.AutoTransform.Time = 50;
    cscp.AutoTransform.InitialRect = {0,0,0,0};
    cscp.AutoTransformFadeOut.AccelCaptureTime = 1;
    cscp.AutoTransformFadeOut.FadeOutTime = 20;
    cscp.AutoAlphaFade.FadeTime = 10;
    cscp.AutoAlphaFade.AlphaMin = 0;
    cscp.AutoAlphaFade.Activate = 0;
    cscp.AutoAlphaFade.ShowHide = 1;

    idcnt = csc.csCNT_newContainer(idp, cscp);

    /********************************************************************************/
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    if(orient==0)
    {
        cscp.Geometry= {geometry.left+20,geometry.top,geometry.right-40,geometry.bottom};
        cscp.DCSizes = {1400,(unsigned int)geometry.bottom};
    }
    else
    {
        cscp.Geometry= {geometry.left,geometry.top+20,geometry.right,geometry.bottom-40};
        cscp.DCSizes = {(unsigned int)geometry.right,1000};
    }
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=0;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=0;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.05;//zzzzzzzzzzzzzzzzzzzzzzzzzzz
    cscp.DCSizes = {1366,30};
    cscp.MinTrackSize= {1,1};
    cscp.MaxTrackSize= {1366,1000};
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= bkgcol;
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text = "";
    cscp.GeometryLink.RightLinkEvent_target = GLINK_SIZE;
    cscp.GeometryLink.RightLinkEvent_source = GLINK_SIZE|GLINK_POSITION;
    cscp.GeometryLink.idhwndRight = idcnt;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {50,40,40};
    cscp.MHGradient.Color2 = bkgcol;
    cscp.MouseHoverTime = 3;
    cscp.AutoTransform.Type = AUTO_TRANSF_LENGTH;
    cscp.AutoTransform.Time = 50;
    cscp.AutoTransform.InitialRect = {0,0,0,0};

    idb = csc.csCNT_newContainer(idcnt, cscp);

    /********************************************************************************/
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    if(orient==0)
        cscp.Geometry= {geometry.left+40,geometry.top,geometry.right-80,geometry.bottom};
    else
        cscp.Geometry= {geometry.left,geometry.top+40,geometry.right,geometry.bottom-80};
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=0;
    if(orient==0)
    {
        cscp.CaptionDirection=CAPTION_DIRECTION_X;
        cscp.CaptionAreaPos=1;
        cscp.CaptionAreaLength=geometry.bottom;
        cscp.DCSizes = {1400,(unsigned int)geometry.bottom};
    }
    else
    {
        cscp.CaptionDirection=CAPTION_DIRECTION_Y;
        cscp.CaptionAreaPos=2;
        cscp.CaptionAreaLength=geometry.right;
        cscp.DCSizes = {(unsigned int)geometry.right,1000};
    }
    cscp.CaptionDirection_pos = 0;
    cscp.BlockedWithinParent = 1;
    cscp.XMinTrackPosition_extra = 0;
    cscp.DcZoomIncrement=0.05;//zzzzzzzzzzzzzzzzzzzzzzzzzzz
    cscp.MinTrackSize= {1,1};
    cscp.MaxTrackSize= {1366,1000};
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= bkgcol;
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text = "";
    cscp.GeometryLink.RightLinkEvent_target = GLINK_SIZE;
    cscp.GeometryLink.RightLinkEvent_source = GLINK_SIZE|GLINK_POSITION;
    cscp.GeometryLink.idhwndRight = idcnt;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {50,40,40};
    cscp.MHGradient.Color2 = bkgcol;
    cscp.MouseHoverTime = 3;
    cscp.AutoTransform.Type = AUTO_TRANSF_LENGTH;
    cscp.AutoTransform.Time = 50;
    cscp.AutoTransform.InitialRect = {0,0,0,0};
    cscp.AutoTransformFadeOut.AccelCaptureTime = 1;
    cscp.AutoTransformFadeOut.FadeOutTime = 20;

    idc = csc.csCNT_newContainer(idb, cscp);

    /********************************************************************************/
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    if(orient==0)
    {
        cscp.Geometry= {geometry.left,geometry.top,20,geometry.bottom};
        cscp.DCSizes = {20,(unsigned int)geometry.bottom};
    }
    else
    {
        cscp.Geometry= {geometry.left,geometry.top,geometry.right,20};
        cscp.DCSizes = {(unsigned int)geometry.right,20};
    }
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=0;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=0;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.05;//zzzzzzzzzzzzzzzzzzzzzzzzzzz
    cscp.DCSizes = {1366,30};
    cscp.MinTrackSize= {1,1};
    cscp.MaxTrackSize= {1366,1000};
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= bkgcol;
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text = "";
    cscp.GeometryLink.RightLinkEvent_target = GLINK_SIZE;
    cscp.GeometryLink.RightLinkEvent_source = GLINK_SIZE|GLINK_POSITION;
    cscp.GeometryLink.idhwndRight = idcnt;
    cscp.MHGradient.Image1 = "C:\\Users\\Phil Az\\OneDrive\\Bureau\\CppCodes\\Win32gui\\BCGUI\\BCGUI\\img\\arrowleft2.bmp";
    cscp.MHGradient.Image2 = "C:\\Users\\Phil Az\\OneDrive\\Bureau\\CppCodes\\Win32gui\\BCGUI\\BCGUI\\img\\arrowleft.bmp";
    cscp.MHGradient.GradientType = CS_GRAD_IMAGE;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {50,40,40};
    cscp.MHGradient.Color2 = bkgcol;
    cscp.MouseHoverTime = 3;
    cscp.AutoTransform.Type = AUTO_TRANSF_LENGTH;
    cscp.AutoTransform.Time = 50;
    cscp.AutoTransform.InitialRect = {0,0,0,0};

    idprev = csc.csCNT_newContainer(idcnt, cscp);
}

csSBAR::~csSBAR()
{
    //dtor
}
