#include <gui/screen_screen/screenView.hpp>
#include <gui/screen_screen/screenPresenter.hpp>

screenPresenter::screenPresenter(screenView& v)
    : view(v)
{

}

void screenPresenter::activate()
{

}

void screenPresenter::deactivate()
{

}

void screenPresenter::m_BSP_LED_on()
{
	model->m_BSP_LED_on();
}

void screenPresenter::m_BSP_LED_off()
{
	model->m_BSP_LED_off();
}
