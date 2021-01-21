#include <string.h>
//#include <types.h>

int	strlen(const char *str){
    int len = 0;
    
    while(*str++ != '\0'){
        len++;
    }
    
    return len;
}

char *	strcpy(char *dst, const char *src){
    char *dp = dst;
    
    while((*dp++ = *src++) != '\0');
    
    return dst;
}

char *	strncpy(char *dst, const char *src, size_t size){
    char *dp = dst;
    
    while(size-- > 0){
        *dp++ = *src;
        if(*src != '\0'){
            src++;
        }
    }
    
    return dst;
}

char *	strcat(char *dst, const char *src){
    int len = strlen(dst);
    dst = strcpy(dst + len, src);
    return dst;
}

int	strcmp(const char *str1, const char *str2){
    while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2){
        str1++;
        str2++;
    }
    
    if(*str1 == '\0' && *str2 != '\0'){
        return -1;
    }else if(*str2 == '\0' && *str1 != '\0'){
        return 1;
    }
    
    return (int)(*str1 - *str2);
}

int	strncmp(const char *str1, const char *str2, size_t size){
    while(size-- && *str1 != '\0' && *str2 != '\0' && *str1 == *str2){
        str1++;
        str2++;
    }
    
    if(*str1 == '\0' && *str2 != '\0'){
        return -1;
    }else if(*str2 == '\0' && *str1 != '\0'){
        return 1;
    }
    
    return (int)(*str1 - *str2);
}

char *strstr(const char *haystack, const char *needle){
    //remain to be add
}

void *	memmove(void *dst, const void *src, size_t len){
    uint8_t *dp = (uint8_t *)dst;
    const uint8_t *sp = (const uint8_t *)src;
    
    if(sp < dp && sp + len > dp){
        sp += len;
        dp += len;
        while(len-- > 0){
            *--dp = *--sp;
        }
    }else{
        while(len-- > 0){
            *dp++ = *sp++;
        }
    }
    
    return dst;
}

void *	memset(void *dst, uint8_t c, size_t len){
    uint8_t *dp = (uint8_t *)dst;
    
    while(len-- > 0){
        *dp++ = c;
    }
    
    return dst;
}
