# CSV Operations Examples

## Reading CSV Files

### Basic CSV Reading

```c
#include <tablr/tablr.h>

int main(void) {
    /* Read with default settings */
    TablrDataFrame* df = tablr_read_csv_default("data.csv");
    
    if (df) {
        printf("Loaded %zu rows and %zu columns\n",
               tablr_dataframe_nrows(df),
               tablr_dataframe_ncols(df));
        
        tablr_dataframe_print(df);
        tablr_dataframe_free(df);
    }
    
    return 0;
}
```

### Custom Delimiter

```c
#include <tablr/tablr.h>

int main(void) {
    /* Read tab-separated file */
    TablrDataFrame* df = tablr_read_csv("data.tsv", '\t', true);
    
    /* Read semicolon-separated file */
    TablrDataFrame* df2 = tablr_read_csv("data.csv", ';', true);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(df2);
    
    return 0;
}
```

## Writing CSV Files

### Basic CSV Writing

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Add data... */
    
    /* Write to CSV */
    if (tablr_to_csv_default(df, "output.csv")) {
        printf("Successfully wrote to output.csv\n");
    }
    
    tablr_dataframe_free(df);
    
    return 0;
}
```

### Custom Format

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("input.csv");
    
    /* Write with custom delimiter, no header */
    tablr_to_csv(df, "output.tsv", '\t', false);
    
    tablr_dataframe_free(df);
    
    return 0;
}
```

## Processing Pipeline

```c
#include <tablr/tablr.h>

int main(void) {
    /* Read */
    TablrDataFrame* df = tablr_read_csv_default("input.csv");
    
    /* Process */
    TablrDataFrame* filtered = tablr_dataframe_head(df, 100);
    TablrDataFrame* sorted = tablr_dataframe_sort(filtered, "Value", true);
    
    /* Write */
    tablr_to_csv_default(sorted, "output.csv");
    
    /* Cleanup */
    tablr_dataframe_free(df);
    tablr_dataframe_free(filtered);
    tablr_dataframe_free(sorted);
    
    return 0;
}
```
