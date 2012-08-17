/*
 *      Copyright (C) 2010-2012 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "stdafx.h"
#include "VideoSettingsProp.h"
#include "Media.h"

#include <Commctrl.h>

#include "resource.h"

CLAVVideoSettingsProp::CLAVVideoSettingsProp(LPUNKNOWN pUnk, HRESULT* phr)
  : CBaseDSPropPage(NAME("LAVVideoProp"), pUnk, IDD_PROPPAGE_VIDEO_SETTINGS, IDS_SETTINGS), m_pVideoSettings(NULL)
{
}

CLAVVideoSettingsProp::~CLAVVideoSettingsProp()
{
}

HRESULT CLAVVideoSettingsProp::OnConnect(IUnknown *pUnk)
{
  if (pUnk == NULL)
  {
    return E_POINTER;
  }
  ASSERT(m_pVideoSettings == NULL);
  HRESULT hr = pUnk->QueryInterface(&m_pVideoSettings);
  if (FAILED(hr))
    return hr;
  hr =  pUnk->QueryInterface(&m_pVideoStatus);
  if (FAILED(hr))
    return hr;
  return S_OK;
}

HRESULT CLAVVideoSettingsProp::OnDisconnect()
{
  SafeRelease(&m_pVideoSettings);
  SafeRelease(&m_pVideoStatus);
  return S_OK;
}

HRESULT CLAVVideoSettingsProp::OnApplyChanges()
{
  ASSERT(m_pVideoSettings != NULL);
  ASSERT(m_pVideoStatus != NULL);
  HRESULT hr = S_OK;
  BOOL bFlag;
  DWORD dwVal;
  
  dwVal = (BOOL)SendDlgItemMessage(m_Dlg, IDC_STREAMAR, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetStreamAR(dwVal);

  dwVal = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SOFT_TC, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetSoftTelecineMode(dwVal);

  dwVal = (DWORD)SendDlgItemMessage(m_Dlg, IDC_THREADS, CB_GETCURSEL, 0, 0);
  m_pVideoSettings->SetNumThreads(dwVal);

  dwVal = (DWORD)SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_GETCURSEL, 0, 0);
  m_pVideoSettings->SetDeintFieldOrder((LAVDeintFieldOrder)dwVal);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_DEINT_AGGRESSIVE, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetDeintAggressive(bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_DEINT_FORCE, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetDeintForce(bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_DEINT_PROGRESSIVE, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetDeintTreatAsProgressive(bFlag);

  BOOL bPixFmts[LAVOutPixFmt_NB] = {0};
  for (int i = 0; i < LAVOutPixFmt_NB; ++i) {
    bPixFmts[i] = TRUE;
  }

  bPixFmts[LAVOutPixFmt_YV12] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_YV12, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_NV12] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_NV12, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_P010] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_P010, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_P016] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_P016, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_YUY2] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_YUY2, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_UYVY] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_UYVY, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_P210] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_P210, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_v210] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_V210, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_P216] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_P216, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_YV24] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_YV24, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_AYUV] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_AYUV, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_Y410] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_Y410, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_v410] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_V410, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_Y416] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_Y416, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_RGB32] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_RGB32, BM_GETCHECK,0, 0);
  bPixFmts[LAVOutPixFmt_RGB24] = (BOOL)SendDlgItemMessage(m_Dlg, IDC_OUT_RGB24, BM_GETCHECK,0, 0);

  for (int i = 0; i < LAVOutPixFmt_NB; ++i) {
    m_pVideoSettings->SetPixelFormat((LAVOutPixFmts)i, bPixFmts[i]);
  }

  BOOL bRGBAuto = (BOOL)SendDlgItemMessage(m_Dlg, IDC_RGBOUT_AUTO, BM_GETCHECK, 0, 0);
  BOOL bRGBTV = (BOOL)SendDlgItemMessage(m_Dlg, IDC_RGBOUT_TV, BM_GETCHECK, 0, 0);
  BOOL bRGBPC = (BOOL)SendDlgItemMessage(m_Dlg, IDC_RGBOUT_PC, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetRGBOutputRange(bRGBAuto ? 0 : bRGBTV ? 1 : 2);

  dwVal = (DWORD)SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_GETCURSEL, 0, 0);
  m_pVideoSettings->SetHWAccel((LAVHWAccel)dwVal);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWACCEL_H264, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelCodec(HWCodec_H264, bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWACCEL_VC1, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelCodec(HWCodec_VC1, bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWACCEL_MPEG2, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelCodec(HWCodec_MPEG2, bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWACCEL_MPEG4, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelCodec(HWCodec_MPEG4, bFlag);

  BOOL bWeave = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_WEAVE, BM_GETCHECK, 0, 0);
  BOOL bBOB = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_BOB, BM_GETCHECK, 0, 0);
  BOOL bAdaptive = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_ADAPTIVE, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelDeintMode(bWeave ? HWDeintMode_Weave : bBOB ? HWDeintMode_BOB : HWDeintMode_Hardware);

  BOOL bFilm = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_OUT_FILM, BM_GETCHECK, 0, 0);
  //BOOL bVideo = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_OUT_VIDEO, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelDeintOutput(bFilm ? DeintOutput_FramePer2Field : DeintOutput_FramePerField);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_HWDEINT_HQ, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetHWAccelDeintHQ(bFlag);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SWDEINT_ENABLE, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetSWDeintMode(bFlag ? SWDeintMode_YADIF : SWDeintMode_None);

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SWDEINT_OUT_FILM, BM_GETCHECK, 0, 0);
  //BOOL bVideo = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SWDEINT_OUT_VIDEO, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetSWDeintOutput(bFlag ? DeintOutput_FramePer2Field : DeintOutput_FramePerField);

  BOOL bOrdered = (BOOL)SendDlgItemMessage(m_Dlg, IDC_DITHER_ORDERED, BM_GETCHECK, 0, 0);
  BOOL bRandom = (BOOL)SendDlgItemMessage(m_Dlg, IDC_DITHER_RANDOM, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetDitherMode(bOrdered ? LAVDither_Ordered : LAVDither_Random);

  LoadData();

  return hr;
} 

HRESULT CLAVVideoSettingsProp::OnActivate()
{
  HRESULT hr = S_OK;
  INITCOMMONCONTROLSEX icc;
  icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icc.dwICC = ICC_BAR_CLASSES | ICC_STANDARD_CLASSES;
  if (InitCommonControlsEx(&icc) == FALSE)
  {
    return E_FAIL;
  }
  ASSERT(m_pVideoSettings != NULL);

  const WCHAR *version = TEXT(LAV_VIDEO) L" " TEXT(LAV_VERSION_STR);
  SendDlgItemMessage(m_Dlg, IDC_LAVVIDEO_FOOTER, WM_SETTEXT, 0, (LPARAM)version);

  WCHAR stringBuffer[512] = L"Auto";

  // Init the Combo Box
  SendDlgItemMessage(m_Dlg, IDC_THREADS, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(m_Dlg, IDC_THREADS, CB_ADDSTRING, 0, (LPARAM)stringBuffer);

  for (unsigned i = 1; i <= 16; ++i) {
    swprintf_s(stringBuffer, L"%d", i);
    SendDlgItemMessage(m_Dlg, IDC_THREADS, CB_ADDSTRING, 0, (LPARAM)stringBuffer);
  }

  addHint(IDC_THREADS, L"Enable Multi-Threading for codecs that support it.\nAuto will automatically use the maximum number of threads suitable for your CPU. Using 1 thread disables multi-threading.\n\nMT decoding is supported for H264, MPEG2, MPEG4, VP8, VP3/Theora, DV and HuffYUV");

  addHint(IDC_STREAMAR, L"Checked - Stream AR will be used.\nUnchecked - Frame AR will not be used.\nIndeterminate (Auto) - Stream AR will not be used on files with a container AR (recommended).");
  addHint(IDC_SOFT_TC, L"Unchecked - Soft Telecine will be handled by the renderer.\nChecked - Soft Telecine will be removed and timestamps adjusted.\nIndeterminate (Auto) - Soft Telecine flags will be removed, but timestamps left alone.");

  WCHAR hwAccelNone[] = L"None";
  WCHAR hwAccelCUDA[] = L"NVIDIA CUVID";
  WCHAR hwAccelQuickSync[] = L"Intel\xae QuickSync";
  WCHAR hwAccelDXVA2CB[] = L"DXVA2 (copy-back)";
  WCHAR hwAccelDXVA2N[] = L"DXVA2 (native)";
  SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_ADDSTRING, 0, (LPARAM)hwAccelNone);
  SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_ADDSTRING, 0, (LPARAM)hwAccelCUDA);
  SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_ADDSTRING, 0, (LPARAM)hwAccelQuickSync);
  SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_ADDSTRING, 0, (LPARAM)hwAccelDXVA2CB);
  SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_ADDSTRING, 0, (LPARAM)hwAccelDXVA2N);

  // Init the fieldorder Combo Box
  SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_RESETCONTENT, 0, 0);
  WideStringFromResource(stringBuffer, IDS_FIELDORDER_AUTO);
  SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_ADDSTRING, 0, (LPARAM)stringBuffer);
  WideStringFromResource(stringBuffer, IDS_FIELDORDER_TOP);
  SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_ADDSTRING, 0, (LPARAM)stringBuffer);
  WideStringFromResource(stringBuffer, IDS_FIELDORDER_BOTTOM);
  SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_ADDSTRING, 0, (LPARAM)stringBuffer);

  addHint(IDC_HWACCEL_MPEG4, L"EXPERIMENTAL! The MPEG4-ASP decoder is known to be unstable! Use at your own peril!");

  addHint(IDC_DEINT_AGGRESSIVE, L"Force deinterlacing of all frames if the stream is flagged interlaced.");
  addHint(IDC_DEINT_FORCE, L"Force deinterlacing of all frames flagged as progressive (always).");
  addHint(IDC_DEINT_PROGRESSIVE, L"Treat all streams/frames as progressive, disabling all forms of deinterlacing completely.\n\nNOTE: This includes deinterlacing by the renderer.\nIf this option is checked, LAV Video will no longer tell the renderer that the material is interlaced.");

  addHint(IDC_HWDEINT_OUT_FILM, L"Deinterlace in \"Film\" Mode.\nFor every pair of interlaced fields, one frame will be created, resulting in 25/30 fps.");
  addHint(IDC_HWDEINT_OUT_VIDEO, L"Deinterlace in \"Video\" Mode. (Recommended)\nFor every interlaced field, one frame will be created, resulting in 50/60 fps.");

  addHint(IDC_HWDEINT_HQ, L"Instruct the decoder to use the maximum quality possible.\nThis will cost performance, it is however required for the best deinterlacing quality.\n\nNOTE: This option has no effect on Windows XP.");

  addHint(IDC_DITHER_ORDERED, L"Ordered Dithering uses a static pattern, resulting in very smooth and regular pattern. However, in some cases the regular pattern can be visible and distracting.");
  addHint(IDC_DITHER_RANDOM, L"Random Dithering uses random noise to dither the video frames. This has the advantage of not creating any visible pattern, at the downside of increasing the noise floor slightly.");

  hr = LoadData();
  if (SUCCEEDED(hr)) {
    SendDlgItemMessage(m_Dlg, IDC_THREADS, CB_SETCURSEL, m_dwNumThreads, 0);

    SendDlgItemMessage(m_Dlg, IDC_STREAMAR, BM_SETCHECK, m_StreamAR, 0);
    SendDlgItemMessage(m_Dlg, IDC_SOFT_TC, BM_SETCHECK, m_SoftTCMode, 0);

    SendDlgItemMessage(m_Dlg, IDC_DEINT_FIELDORDER, CB_SETCURSEL, m_DeintFieldOrder, 0);

    SendDlgItemMessage(m_Dlg, IDC_DEINT_AGGRESSIVE, BM_SETCHECK, m_DeintAggressive, 0);
    SendDlgItemMessage(m_Dlg, IDC_DEINT_FORCE, BM_SETCHECK, m_DeintForce, 0);
    SendDlgItemMessage(m_Dlg, IDC_DEINT_PROGRESSIVE, BM_SETCHECK, m_DeintProgressive, 0);

    SendDlgItemMessage(m_Dlg, IDC_OUT_YV12, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_YV12], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_NV12, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_NV12], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_P010, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_P010], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_P016, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_P016], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_YUY2, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_YUY2], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_UYVY, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_UYVY], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_P210, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_P210], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_V210, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_v210], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_P216, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_P216], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_YV24, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_YV24], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_AYUV, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_AYUV], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_Y410, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_Y410], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_V410, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_v410], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_Y416, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_Y416], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_RGB32, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_RGB32], 0);
    SendDlgItemMessage(m_Dlg, IDC_OUT_RGB24, BM_SETCHECK, m_bPixFmts[LAVOutPixFmt_RGB24], 0);

    SendDlgItemMessage(m_Dlg, IDC_RGBOUT_AUTO, BM_SETCHECK, (m_dwRGBOutput == 0), 0);
    SendDlgItemMessage(m_Dlg, IDC_RGBOUT_TV, BM_SETCHECK, (m_dwRGBOutput == 1), 0);
    SendDlgItemMessage(m_Dlg, IDC_RGBOUT_PC, BM_SETCHECK, (m_dwRGBOutput == 2), 0);

    SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_SETCURSEL, m_HWAccel, 0);
    SendDlgItemMessage(m_Dlg, IDC_HWACCEL_H264, BM_SETCHECK, m_HWAccelCodecs[HWCodec_H264], 0);
    SendDlgItemMessage(m_Dlg, IDC_HWACCEL_VC1, BM_SETCHECK, m_HWAccelCodecs[HWCodec_VC1], 0);
    SendDlgItemMessage(m_Dlg, IDC_HWACCEL_MPEG2, BM_SETCHECK, m_HWAccelCodecs[HWCodec_MPEG2], 0);
    SendDlgItemMessage(m_Dlg, IDC_HWACCEL_MPEG4, BM_SETCHECK, m_HWAccelCodecs[HWCodec_MPEG4], 0);

    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_WEAVE, BM_SETCHECK, (m_HWDeintAlgo == HWDeintMode_Weave), 0);
    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_BOB, BM_SETCHECK, (m_HWDeintAlgo == HWDeintMode_BOB), 0);
    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_ADAPTIVE, BM_SETCHECK, (m_HWDeintAlgo == HWDeintMode_Hardware), 0);

    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_OUT_FILM, BM_SETCHECK, (m_HWDeintOutMode == DeintOutput_FramePer2Field), 0);
    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_OUT_VIDEO, BM_SETCHECK, (m_HWDeintOutMode == DeintOutput_FramePerField), 0);

    SendDlgItemMessage(m_Dlg, IDC_HWDEINT_HQ, BM_SETCHECK, m_HWDeintHQ, 0);

    SendDlgItemMessage(m_Dlg, IDC_SWDEINT_ENABLE, BM_SETCHECK, m_SWDeint, 0);
    SendDlgItemMessage(m_Dlg, IDC_SWDEINT_OUT_FILM, BM_SETCHECK, (m_SWDeintOutMode == DeintOutput_FramePer2Field), 0);
    SendDlgItemMessage(m_Dlg, IDC_SWDEINT_OUT_VIDEO, BM_SETCHECK, (m_SWDeintOutMode == DeintOutput_FramePerField), 0);

    SendDlgItemMessage(m_Dlg, IDC_DITHER_ORDERED, BM_SETCHECK, (m_DitherMode == LAVDither_Ordered), 0);
    SendDlgItemMessage(m_Dlg, IDC_DITHER_RANDOM, BM_SETCHECK, (m_DitherMode == LAVDither_Random), 0);

    UpdateHWOptions();
  }

  const WCHAR *decoder = m_pVideoStatus->GetActiveDecoderName();
  SendDlgItemMessage(m_Dlg, IDC_ACTIVE_DECODER, WM_SETTEXT, 0, (LPARAM)(decoder ? decoder : L"<inactive>"));

  return hr;
}

HRESULT CLAVVideoSettingsProp::UpdateHWOptions()
{
  LAVHWAccel hwAccel = (LAVHWAccel)SendDlgItemMessage(m_Dlg, IDC_HWACCEL, CB_GETCURSEL, 0, 0);

  DWORD dwSupport = m_pVideoSettings->CheckHWAccelSupport(hwAccel);
  BOOL bEnabled = (hwAccel != HWAccel_None) && dwSupport;
  BOOL bHWDeint = bEnabled && (hwAccel == HWAccel_CUDA); // || hwAccel == HWAccel_QuickSync);
  BOOL bCUDAOnly = bEnabled && (hwAccel == HWAccel_CUDA);

  EnableWindow(GetDlgItem(m_Dlg, IDC_HWACCEL_H264), bEnabled);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWACCEL_VC1), bEnabled);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWACCEL_MPEG2), bEnabled);

  EnableWindow(GetDlgItem(m_Dlg, IDC_HWACCEL_MPEG4), bCUDAOnly);

  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_WEAVE), bHWDeint);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_BOB), bCUDAOnly);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_ADAPTIVE), bHWDeint);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_OUT_FILM), bHWDeint);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_OUT_VIDEO), bHWDeint);
  EnableWindow(GetDlgItem(m_Dlg, IDC_HWDEINT_HQ), bCUDAOnly);

  WCHAR hwAccelEmpty[] = L"";
  WCHAR hwAccelUnavailable[] = L"Not available";
  WCHAR hwAccelAvailable[]   = L"Available";
  WCHAR hwAccelActive[]      = L"Active";

  SendDlgItemMessage(m_Dlg, IDC_HWACCEL_AVAIL, WM_SETTEXT, 0, (LPARAM)(hwAccel == HWAccel_None ? hwAccelEmpty : dwSupport == 0 ? hwAccelUnavailable : dwSupport == 1 ? hwAccelAvailable : hwAccelActive));

  return S_OK;
}

HRESULT CLAVVideoSettingsProp::LoadData()
{
  HRESULT hr = S_OK;
  
  m_dwNumThreads    = m_pVideoSettings->GetNumThreads();
  m_StreamAR        = m_pVideoSettings->GetStreamAR();
  m_DeintFieldOrder = m_pVideoSettings->GetDeintFieldOrder();
  m_DeintAggressive = m_pVideoSettings->GetDeintAggressive();
  m_DeintForce      = m_pVideoSettings->GetDeintForce();
  m_dwRGBOutput     = m_pVideoSettings->GetRGBOutputRange();

  for (int i = 0; i < LAVOutPixFmt_NB; ++i) {
    m_bPixFmts[i] = m_pVideoSettings->GetPixelFormat((LAVOutPixFmts)i);
  }

  m_HWAccel = m_pVideoSettings->GetHWAccel();
  for (int i = 0; i < HWCodec_NB; ++i) {
    m_HWAccelCodecs[i] = m_pVideoSettings->GetHWAccelCodec((LAVVideoHWCodec)i);
  }

  m_HWDeintAlgo = m_pVideoSettings->GetHWAccelDeintMode();
  m_HWDeintOutMode = m_pVideoSettings->GetHWAccelDeintOutput();
  m_HWDeintHQ = m_pVideoSettings->GetHWAccelDeintHQ();

  m_SWDeint = m_pVideoSettings->GetSWDeintMode() == SWDeintMode_YADIF;
  m_SWDeintOutMode = m_pVideoSettings->GetSWDeintOutput();

  m_DeintProgressive = m_pVideoSettings->GetDeintTreatAsProgressive();
  m_DitherMode = m_pVideoSettings->GetDitherMode();

  m_SoftTCMode = m_pVideoSettings->GetSoftTelecineMode();

  return hr;
}

INT_PTR CLAVVideoSettingsProp::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT lValue;
  BOOL bValue;
  switch (uMsg)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == IDC_STREAMAR && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != m_StreamAR) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_THREADS) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), CB_GETCURSEL, 0, 0);
      if (lValue != m_dwNumThreads) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DEINT_FIELDORDER && HIWORD(wParam) == CBN_SELCHANGE) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), CB_GETCURSEL, 0, 0);
      if (lValue != m_DeintFieldOrder) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DEINT_AGGRESSIVE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_DeintAggressive) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DEINT_FORCE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_DeintForce) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DEINT_PROGRESSIVE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_DeintProgressive) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_YV12 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_YV12]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_NV12 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_NV12]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_P010 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_P010]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_P016 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_P016]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_YUY2 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_YUY2]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_UYVY && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_UYVY]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_P210 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_P210]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_V210 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_v210]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_P216 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_P216]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_YV24 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_YV24]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_AYUV && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_AYUV]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_Y410 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_Y410]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_V410 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_v410]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_Y416 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_Y416]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_RGB32 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_RGB32]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_OUT_RGB24 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bPixFmts[LAVOutPixFmt_RGB24]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_RGBOUT_AUTO && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != (m_dwRGBOutput == 0)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_RGBOUT_TV && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != (m_dwRGBOutput == 1)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_RGBOUT_PC && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != (m_dwRGBOutput == 2)) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_HWACCEL) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), CB_GETCURSEL, 0, 0);
      if (lValue != m_HWAccel) {
        SetDirty();
      }
      UpdateHWOptions();
    } else if (LOWORD(wParam) == IDC_HWACCEL_H264 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_HWAccelCodecs[HWCodec_H264]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWACCEL_VC1 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_HWAccelCodecs[HWCodec_VC1]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWACCEL_MPEG2 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_HWAccelCodecs[HWCodec_MPEG2]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWACCEL_MPEG4 && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_HWAccelCodecs[HWCodec_MPEG4]) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_WEAVE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_HWDeintAlgo == HWDeintMode_Weave)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_BOB && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_HWDeintAlgo == HWDeintMode_BOB)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_ADAPTIVE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_HWDeintAlgo == HWDeintMode_Hardware)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_OUT_FILM && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_HWDeintOutMode == DeintOutput_FramePer2Field)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_OUT_VIDEO && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_HWDeintOutMode == DeintOutput_FramePerField)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_HWDEINT_HQ && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_HWDeintHQ) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_SWDEINT_OUT_FILM && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_SWDeintOutMode == DeintOutput_FramePer2Field)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_SWDEINT_OUT_VIDEO && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != (m_SWDeintOutMode == DeintOutput_FramePerField)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_SWDEINT_ENABLE && HIWORD(wParam) == BN_CLICKED) {
      bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_SWDeint) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DITHER_ORDERED && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != (m_DitherMode == LAVDither_Ordered)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_DITHER_RANDOM && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != (m_DitherMode == LAVDither_Random)) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_SOFT_TC && HIWORD(wParam) == BN_CLICKED) {
      lValue = SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (lValue != m_SoftTCMode) {
        SetDirty();
      }
    }
    break;
  }
  // Let the parent class handle the message.
  return __super::OnReceiveMessage(hwnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Format Configurations

CLAVVideoFormatsProp::CLAVVideoFormatsProp(LPUNKNOWN pUnk, HRESULT* phr)
  : CBaseDSPropPage(NAME("LAVVideoFormats"), pUnk, IDD_PROPPAGE_FORMATS, IDS_FORMATS), m_pVideoSettings(NULL)
{
}

CLAVVideoFormatsProp::~CLAVVideoFormatsProp()
{
}

HRESULT CLAVVideoFormatsProp::OnConnect(IUnknown *pUnk)
{
  if (pUnk == NULL)
  {
    return E_POINTER;
  }
  ASSERT(m_pVideoSettings == NULL);
  return pUnk->QueryInterface(&m_pVideoSettings);
}

HRESULT CLAVVideoFormatsProp::OnDisconnect()
{
  SafeRelease(&m_pVideoSettings);
  return S_OK;
}


HRESULT CLAVVideoFormatsProp::OnApplyChanges()
{
  ASSERT(m_pVideoSettings != NULL);
  HRESULT hr = S_OK;

  HWND hlv = GetDlgItem(m_Dlg, IDC_CODECS);

  // Get checked state
  BOOL bFlag;
  for (int nItem = 0; nItem < ListView_GetItemCount(hlv); nItem++) {
    bFlag = ListView_GetCheckState(hlv, nItem);
    m_pVideoSettings->SetFormatConfiguration((LAVVideoCodec)nItem, bFlag);
  }

  bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_CODECS_MSWMVDMO, BM_GETCHECK, 0, 0);
  m_pVideoSettings->SetUseMSWMV9Decoder(bFlag);

  LoadData();

  return hr;
}

HRESULT CLAVVideoFormatsProp::OnActivate()
{
  HRESULT hr = S_OK;
  INITCOMMONCONTROLSEX icc;
  icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icc.dwICC = ICC_BAR_CLASSES | ICC_STANDARD_CLASSES | ICC_LISTVIEW_CLASSES;
  if (InitCommonControlsEx(&icc) == FALSE)
  {
    return E_FAIL;
  }
  ASSERT(m_pVideoSettings != NULL);

  // Setup ListView control for format configuration
  HWND hlv = GetDlgItem(m_Dlg, IDC_CODECS);
  ListView_SetExtendedListViewStyle(hlv, LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

  int nCol = 1;
  LVCOLUMN lvc = {LVCF_WIDTH, 0, 20, 0};
  ListView_InsertColumn(hlv, 0, &lvc);
  ListView_AddCol(hlv, nCol,  85, L"Codec", false);
  ListView_AddCol(hlv, nCol, 400, L"Description", false);

  ListView_DeleteAllItems(hlv);
  ListView_SetItemCount(hlv, Codec_NB);

  // Create entrys for the formats
  LVITEM lvi;
  memset(&lvi, 0, sizeof(lvi));
  lvi.mask = LVIF_TEXT|LVIF_PARAM;

  int nItem = 0;
  for (nItem = 0; nItem < Codec_NB; ++nItem) {
    const codec_config_t *config = get_codec_config((LAVVideoCodec)nItem);

    // Create main entry
    lvi.iItem = nItem + 1;
    ListView_InsertItem(hlv, &lvi);

    // Set sub item texts
    ATL::CA2W name(config->name);
    ListView_SetItemText(hlv, nItem, 1, (LPWSTR)name);

    ATL::CA2W desc(config->description);
    ListView_SetItemText(hlv, nItem, 2, (LPWSTR)desc);
  }

  hr = LoadData();
  if (SUCCEEDED(hr)) {
    // Set checked state
    for (nItem = 0; nItem < ListView_GetItemCount(hlv); nItem++) {
      ListView_SetCheckState(hlv, nItem, m_bFormats[nItem]);
    }
  }

  SendDlgItemMessage(m_Dlg, IDC_CODECS_MSWMVDMO, BM_SETCHECK, m_bWMVDMO, 0);

  return hr;
}

HRESULT CLAVVideoFormatsProp::LoadData()
{
  HRESULT hr = S_OK;
  
  for (unsigned i = 0; i < Codec_NB; ++i)
    m_bFormats[i] = m_pVideoSettings->GetFormatConfiguration((LAVVideoCodec)i) != 0;

  m_bWMVDMO = m_pVideoSettings->GetUseMSWMV9Decoder();

  return hr;
}

INT_PTR CLAVVideoFormatsProp::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == IDC_CODECS_MSWMVDMO && HIWORD(wParam) == BN_CLICKED) {
      BOOL bValue = (BOOL)SendDlgItemMessage(m_Dlg, LOWORD(wParam), BM_GETCHECK, 0, 0);
      if (bValue != m_bWMVDMO) {
        SetDirty();
      }
    }
    break;
  case WM_NOTIFY:
    NMHDR *hdr = (LPNMHDR)lParam;
    if (hdr->idFrom == IDC_CODECS) {
      switch (hdr->code) {
      case LVN_ITEMCHANGED:
        LPNMLISTVIEW nmlv = (LPNMLISTVIEW)lParam;
        BOOL check = ListView_GetCheckState(hdr->hwndFrom, nmlv->iItem);
        if (check != m_bFormats[nmlv->iItem]) {
          SetDirty();
        }
        return TRUE;
      }
    }
    break;
  }
  // Let the parent class handle the message.
  return __super::OnReceiveMessage(hwnd, uMsg, wParam, lParam);
}
