#include <gui/screen_screen/screenView.hpp>

screenView::screenView()
{

}

void screenView::setupScreen()
{
    screenViewBase::setupScreen();
}

void screenView::tearDownScreen()
{
    screenViewBase::tearDownScreen();
}

void screenView::m_BSP_LED_on()
{
	// Override and implement this function in screen
	presenter->m_BSP_LED_on();
}
void screenView::m_BSP_LED_off()
{
	// Override and implement this function in screen
	presenter->m_BSP_LED_off();
}
