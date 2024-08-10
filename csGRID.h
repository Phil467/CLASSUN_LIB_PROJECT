#ifndef CSGRID_H
#define CSGRID_H
#include "csCONTAINER.h"

typedef struct
{
    unsigned x, y;
}UPOINT;


class csGRID
{
    public:
        csGRID(unsigned _idp, RECT _geometry, SIZE _size={2,2}, bool _animate=1);
        RECT newGeometry(SIZE _size, RECT _marg={0});
        RECT realGeometry(RECT geom, RECT _marg);
        RECT realGeometry2(RECT geom, RECT _marg);
        void newContainer(unsigned _id);
        void deleteContainer(unsigned _id);
        void _deleteContainer(csARGS Args);
        void setCntPosition(unsigned _i, unsigned _j);
        void setCntPosition2(unsigned _position);
        virtual ~csGRID();

    protected:
        RECT getNextGeometry(SIZE sz);
        void autoMove(SIZE sz);
        void setMap(RECT r, unsigned _id);
        unsigned getMin(unsigned a, unsigned b);
        unsigned posFromID(unsigned _id);
    private:
        RECT geometry;
        SIZE size;
        bool animate;
        csLIST<csLIST<int>> map;
        csLIST<unsigned> idList;
        csLIST<RECT> geomList;
        csLIST<RECT> margList;
        unsigned dx, dy, idp;
        unsigned nextPos;
};


#endif // CSGRID_H










