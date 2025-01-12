#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void m_BSP_LED_on();
    void m_BSP_LED_off();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
