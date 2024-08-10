#ifndef CSUNITS_H
#define CSUNITS_H


typedef struct
{
    double lon;
    double lat;
}csGEO_COORDS;


class csUNITS
{
    public:
        csUNITS();
        virtual ~csUNITS();

    protected:

    private:
};


double csDedToRad(double angle);
csGEO_COORDS csGeoToUTM(double ldce, double ldcn, bool unit, bool emisph);

#endif // CSUNITS_H
