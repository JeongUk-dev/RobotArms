#pragma once


// CMySlider

class CMySlider : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMySlider)

public:
	CMySlider();
	virtual ~CMySlider();

protected:
	DECLARE_MESSAGE_MAP()


	bool m_bSelected;
	CSliderCtrl* m_sliderCtrl;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	void setMySlider(CSliderCtrl* m_PSliderCtrl);
};


