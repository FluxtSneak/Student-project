#include "matrice.h"   /*matrice*/
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include "pgm.h"

pgm_error pgm_read_from_file(pgm *p, char *filename){
    if(NULL== filename || NULL==p){
        return failure;
    }
    FILE *fp =fopen(filename, "r");
    if(NULL==fp){
        return failure;
    }
    
    char header[80];
    int row;
    int col;
    int max;
    fscanf(fp,"%s %d %d %d", header, &row, &col, &max);
    printf("Votre image fait %d x %d pixels\nle niveau de gris maximal est de : %d\n", row, col, max); 

    matrix_alloc(&(p->pixels), col, row);

    for(int i=0;i<row;i++){
        for (int j=0; j<col;j++){
            uint8_t tmp;
            fread(&tmp, sizeof(uint8_t), 1,fp);
            p->pixels.data[i][j]= (int)tmp;
        }
    }   
    p->max = max;
    
    fclose(fp);
    return success;  

}

pgm_error pgm_write_to_file(pgm *p, char *filename){
    if(NULL== filename || NULL==p){
        return failure;
    }
    
    FILE *fp=fopen(filename,"w");
    fprintf(fp,"%s\n%d %d\n%d\n","P5", p->pixels.m, p->pixels.n, p->max);

    for(int i=0;i<p->pixels.m;i++){
        for(int j=0;j<p->pixels.n;j++){
            fwrite(&(p->pixels.data[i][j]), sizeof(uint8_t),1,fp);
        }
    }
    fclose(fp);
    return success;
}

pgm_error pgm_negative(pgm *neg, const pgm *const orig){
    if(NULL== orig || NULL==neg){
        return failure;
    }

    neg->max=orig->max;
    matrix_clone(&neg->pixels, orig->pixels);
    for(int i=0; i<neg->pixels.m;i++){
        for(int j=0; j<neg->pixels.n;j++){
            neg->pixels.data[i][j]=(neg->max)-(neg->pixels.data[i][j]);
        }
    }

    return success;
}

pgm_error pgm_symmetry_hori(pgm *sym, const pgm *const orig){
    if(NULL== orig || NULL==sym){
        return failure;
    }
    sym->max=orig->max;
    matrix_alloc(&(sym->pixels), orig->pixels.m, orig->pixels.n);
    for(int i=0;i<sym->pixels.m;i++){
        for(int j=0;j<sym->pixels.n;j++){
            sym->pixels.data[i][sym->pixels.n-j-1]=orig->pixels.data[i][j];
        }
    }
    
    return success;
}

pgm_error pgm_symmetry_vert(pgm *sym, const pgm *const orig){
    if(NULL== orig || NULL==sym){
        return failure;
    }
    sym->max=orig->max;
    matrix_alloc(&(sym->pixels), orig->pixels.m, orig->pixels.n);
    for(int i=0;i<sym->pixels.m;i++){
        for(int j=0;j<sym->pixels.n;j++){
            sym->pixels.data[sym->pixels.m-i-1][j]=orig->pixels.data[i][j];
        }
    }
    
    return success;
}

pgm_error pgm_symmetry_cent(pgm *sym, const pgm *const orig){
    if(NULL== orig || NULL==sym){
        return failure;
    }
    sym->max=orig->max;
    matrix_alloc(&(sym->pixels), orig->pixels.m, orig->pixels.n);
    for(int i=0;i<sym->pixels.m;i++){
        for(int j=0;j<sym->pixels.n;j++){
            sym->pixels.data[sym->pixels.m-i-1][sym->pixels.n-j-1]=orig->pixels.data[i][j];
        }
    }

    return success;
}

pgm_error pgm_photomaton(pgm *photomaton, const pgm *const orig){
    if(NULL== orig || NULL==photomaton){
        return failure;
    }
    photomaton->max=orig->max;
    matrix_alloc(&(photomaton->pixels),orig->pixels.m,orig->pixels.n);
    int x, y;
    for(int i=0;i<photomaton->pixels.m;i++){        
        for(int j=0; j<photomaton->pixels.n;j++){                       
            if(j%2==0){
                y=j-j/2;                
            }
            else if(j%2!=0){
                y=j+photomaton->pixels.n/2-j/2-1;                
            }
            if(i%2==0){
                x=i-i/2;
            }
            else if(i%2!=0){
                x=photomaton->pixels.m/2+i-i/2-1;
            }
            photomaton->pixels.data[x][y]=orig->pixels.data[i][j];            
        }        
    }
    return success;
}

pgm_error pgm_crop(pgm *crop, const pgm *const orig, int x0, int x1, int y0, int y1){
    if(NULL== orig || NULL==crop || x0<0 || x1>orig->pixels.m || y1>orig->pixels.n|| y0<0){
        return failure;
    }
    crop->max=orig->max;
    matrix_extract_submatrix(&crop->pixels, orig->pixels, (int32_t)x0, (int32_t)x1, (int32_t)y0, (int32_t)y1);
    
    return success;
}

pgm_error pgm_conv(pgm *conv, const pgm *const orig, const matrix *const kernel){
    if(NULL== orig || NULL==conv || NULL==kernel){
        return failure;
    }
    conv->max=orig->max;
    matrix_alloc(&(conv->pixels), orig->pixels.m, orig->pixels.n);
    int kernel_sum=matrix_sum(*kernel);
    if(kernel_sum<1) kernel_sum=1;
    for(int i=0;i<orig->pixels.m;i++){
        for(int j=0; j<orig->pixels.n;j++){            
            double filter_sum=0.0;

            for(int x=0; x<kernel->m;x++){
                for(int y=0;y<kernel->n;y++){                    
                    int xi= i - kernel->m/2 + x; 
                    int yj= j - kernel->n/2 + y;
                    if(xi>=0 && xi<conv->pixels.m && yj>=0 && yj<conv->pixels.n){                        
                        filter_sum+=orig->pixels.data[xi][yj]*kernel->data[x][y]/kernel_sum;
                    }                    
                }
            }        
            if(filter_sum<0) filter_sum=0;
            if(filter_sum>conv->max)filter_sum=conv->max;
            conv->pixels.data[i][j]= (int)filter_sum;
        }
    }
    return success;
}