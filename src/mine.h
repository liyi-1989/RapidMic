#ifndef _LIBMINE_H
#define _LIBMINE_H

#define LIBMINE_VERSION 035

#ifdef __cplusplus
extern "C" {
#endif
    
    extern int libmine_version;
    typedef struct _mine_result_score
    {
        double mic;
        double mev;
        double mcn;
        double mas;
    } mine_result_score;
    /* The mine_score structure describes the maximum  */
    /* normalized mutual information scores. I[i][j]  */
    /* contains the score using a grid partitioning  */
    /* x-values into i+2 bins and y-values into j+2 bins.  */
    /* p and I are of length m and each I[i] is of length p[i]. */
    typedef struct mine_score
    {
        int m;
        int *p;
        double **I;//��С����Ϊ2*2���ӣ����I[0][0]�ͱ�ʾ2*2�Ļ��֣�������I[1][2]�ͱ�ʾ3*4�Ļ��֣���x���ݻ��ֳ�4�ݲ���y���ݻ��ֳ�3��
    } mine_score;
    /* The mine_problem structure describes the problem. */
    /* x and y are the two variables of length n. */
    typedef struct mine_problem
    {
        int n;
        double *x;
        double *y;
        mine_score *score;
        int *Gy;
        int *idx_x, *idx_y;
        double *x_x, *y_y, *x_y, *y_x;
    } mine_problem;
    
    
    /* The mine_parameter structure describes the MINE parameters. */
    /* alpha is the exponent in B(n) = n^alpha and must be in  */
    /* (0,1], and c determines how many more clumps there will  */
    /* be than columns in every partition. c = 15 meaning that  */
    /* when trying to draw Gx grid lines on the x-axis, the  */
    /* algorithm will start with at most 15*Gx clumps. c must  */
    /* be > 0. */
    typedef struct mine_parameter
    {
        double alpha;
        double c;
    } mine_parameter;
    
    
    
    typedef struct _threadparams
    {
        mine_problem *prob;
        double c;
        int firstPartition;
        int indexBegin;
        int indexEnd;
        
    }threadparams;
    
    typedef struct _varPairs
    {
        int var1;
        int var2;
    }varPairs;
    
    typedef enum _ANALYSISSTYLES {
        OneParis, AllParis, TwoSets, MasterVariable
    }ANALYSISSTYLES;
    
    typedef struct _batchThreadparams
    {
        ANALYSISSTYLES styleType;
        double **inData;
        int *Gy;
        int *scorep;
        int scorem;
        int n;
        varPairs *paris;
        int parisLength;
        mine_result_score *outArray;
        mine_parameter *param;
    }batchThreadparams;
    
    
    int mine_onePairs_analysis(mine_parameter *param, double *x,double *y,int n,mine_result_score *outResult);
    /* Computes the maximum normalized mutual information scores
     * and returns a mine_score structure.
     */
    mine_score *mine_compute_score(mine_problem *prob,
                                   mine_parameter *param);
    
    /* This function checks the parameters. It should be called
     * before calling mine_compute_score(). It returns NULL if
     * the parameters are feasible, otherwise an error message is returned.
     */
    char *check_parameter(mine_parameter *param);
    
    
    /* Returns the Maximal Information Coefficient (MIC). */
    double mic(mine_score *score);
    
    
    /* Returns the Maximum Asymmetry Score (MAS). */
    double mas(mine_score *score);
    
    
    /* Returns the Maximum Edge Value (MEV). */
    double mev(mine_score *score);
    
    
    /* Returns the Minimum Cell Number (MCN). */
    double mcn(mine_score *score);
    
    
    /* This function frees the memory used by a mine_score and 
     *  destroys the score structure.
     */
    void mine_free_score(mine_score **score);
    int mine_masterVariableAnalysis(mine_parameter *param,double **inData,int m,int n,int masterid,mine_result_score *outArray,int outLen );
    int mine_allPairs_analysis(mine_parameter *param, double **inData,int m,int n,mine_result_score *outArray,int outLen );
	int mine_twoSetsAnalysis(mine_parameter *param,double **inDataSet,int m,int n,int betweenid,mine_result_score *outArray,int outLen );
	void get_result_score(mine_score *score,mine_result_score* result);
#ifdef __cplusplus
}
#endif

#endif /* _LIBMINE_H */