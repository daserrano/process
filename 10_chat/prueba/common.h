#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C"{
#endif

    void error(const char *mssg);
    int recibir(int fd, char *buffer);
    int enviar(int fd, const char *mssg);

#ifdef __cplusplus
}
#endif

#endif
