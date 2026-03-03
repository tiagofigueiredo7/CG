#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

class Transformation {
    private:
        float x;
        float y;
        float z;

    public:
        Transformation(float x, float y, float z);  
        Transformation();
        virtual ~Transformation();  // Destrutor virtual serve para garantir que os destrutores 
                                    // das subclasses derivadas sejam chamados em vez de apenas o destrutor da classe base.

        float getX();
        float getY();
        float getZ();

        void setX(float novoX);
        void setY(float novoY);
        void setZ(float novoZ);


};


#endif