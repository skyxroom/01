#include "LaunchDims.h"
#if !defined(LAUNCH_DIMS_H)
#pragma  once
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <cuda_runtime.h>
#include <map>
#include <helpers/CudaLaunchHelper.h>

std::unordered_map<std::string, dim3> algoDimMap = {
    {"random", dim3(GRID_SIZE_RANDOM, BLOCK_SIZE_RANDOM, SHARED_MEM_SIZE_RANDOM)},
    {"diagPart", dim3(GRID_SIZE_DIAG_PART, BLOCK_SIZE_DIAG_PART, SHARED_MEM_SIZE_DIAG_PART)},
    {"logAbsDeterminant", dim3(GRID_SIZE_LOG_ABS_DETERMINANT, BLOCK_SIZE_LOG_ABS_DETERMINANT, SHARED_MEM_SIZE_LOG_ABS_DETERMINANT)},
    {"adjustWeights", dim3(GRID_SIZE_ADJUST_WEIGHTS, BLOCK_SIZE_ADJUST_WEIGHTS, SHARED_MEM_SIZE_ADJUST_WEIGHTS)},
    {"sequenceMask", dim3(GRID_SIZE_SEQUENCE_MASK, BLOCK_SIZE_SEQUENCE_MASK, SHARED_MEM_SIZE_SEQUENCE_MASK)},
    {"segmentSum", dim3(GRID_SIZE_SEGMENT_SUM, BLOCK_SIZE_SEGMENT_SUM, SHARED_MEM_SIZE_SEGMENT_SUM)},
    {"unsortedSegmentSum", dim3(GRID_SIZE_UNSORTED_SEGMENT_SUM, BLOCK_SIZE_UNSORTED_SEGMENT_SUM, SHARED_MEM_SIZE_UNSORTED_SEGMENT_SUM)},
    {"segmentSqrtN", dim3(GRID_SIZE_SEGMENT_SQRTN, BLOCK_SIZE_SEGMENT_SQRTN, SHARED_MEM_SIZE_SEGMENT_SQRTN)},
    {"segmentProd", dim3(GRID_SIZE_SEGMENT_PROD, BLOCK_SIZE_SEGMENT_PROD, SHARED_MEM_SIZE_SEGMENT_PROD)},
    {"unsortedSegmentProd", dim3(GRID_SIZE_UNSORTED_SEGMENT_PROD, BLOCK_SIZE_UNSORTED_SEGMENT_PROD, SHARED_MEM_SIZE_UNSORTED_SEGMENT_PROD)},
    {"segmentMin", dim3(GRID_SIZE_SEGMENT_MIN, BLOCK_SIZE_SEGMENT_MIN, SHARED_MEM_SIZE_SEGMENT_MIN)},
    {"unsortedSegmentMin", dim3(GRID_SIZE_UNSORTED_SEGMENT_MIN, BLOCK_SIZE_UNSORTED_SEGMENT_MIN, SHARED_MEM_SIZE_UNSORTED_SEGMENT_MIN)},
    {"segmentMean", dim3(GRID_SIZE_SEGMENT_MEAN, BLOCK_SIZE_SEGMENT_MEAN, SHARED_MEM_SIZE_SEGMENT_MEAN)},
    {"unsortedSegmentMean", dim3(GRID_SIZE_UNSORTED_SEGMENT_MEAN, BLOCK_SIZE_UNSORTED_SEGMENT_MEAN, SHARED_MEM_SIZE_UNSORTED_SEGMENT_MEAN)},
    {"segmentMax", dim3(GRID_SIZE_SEGMENT_MAX, BLOCK_SIZE_SEGMENT_MAX, SHARED_MEM_SIZE_SEGMENT_MAX)},
    {"unsortedSegmentMax", dim3(GRID_SIZE_UNSORTED_SEGMENT_MAX, BLOCK_SIZE_UNSORTED_SEGMENT_MAX, SHARED_MEM_SIZE_UNSORTED_SEGMENT_MAX)},
    {"matrixDiag", dim3(GRID_SIZE_MATRIX_DIAG, BLOCK_SIZE_MATRIX_DIAG, SHARED_MEM_SIZE_MATRIX_DIAG)},
    {"segmentFillUpSegments", dim3(GRID_SIZE_SEGMENT_FILL_UP_SEGMENTS, BLOCK_SIZE_SEGMENT_FILL_UP_SEGMENTS, SHARED_MEM_SIZE_SEGMENT_FILL_UP_SEGMENTS)},
    {"matrixBand", dim3(GRID_SIZE_MATRIX_BAND, BLOCK_SIZE_MATRIX_BAND, SHARED_MEM_SIZE_MATRIX_BAND)},
    {"lup", dim3(GRID_SIZE_LUP, BLOCK_SIZE_LUP, SHARED_MEM_SIZE_LUP)},
    {"ismax", dim3(GRID_SIZE_ISMAX, BLOCK_SIZE_ISMAX, SHARED_MEM_SIZE_ISMAX)},
    {"ismaxFill", dim3(GRID_SIZE_ISMAX_FILL, BLOCK_SIZE_ISMAX_FILL, SHARED_MEM_SIZE_ISMAX_FILL)},
    {"imageResize", dim3(GRID_SIZE_IMAGE_RESIZE, BLOCK_SIZE_IMAGE_RESIZE, SHARED_MEM_SIZE_IMAGE_RESIZE)},
    {"diag", dim3(GRID_SIZE_DIAG, BLOCK_SIZE_DIAG, SHARED_MEM_SIZE_DIAG)},
    {"confusionMatrix", dim3(GRID_SIZE_CONFUSION_MATRIX, BLOCK_SIZE_CONFUSION_MATRIX, SHARED_MEM_SIZE_CONFUSION_MATRIX)},
    {"tile", dim3(GRID_SIZE_TILE, BLOCK_SIZE_TILE, SHARED_MEM_SIZE_TILE)},
    {"diagonal", dim3(GRID_SIZE_DIAGONAL, BLOCK_SIZE_DIAGONAL, SHARED_MEM_SIZE_DIAGONAL)},
    {"tear", dim3(GRID_SIZE_TEAR, BLOCK_SIZE_TEAR, SHARED_MEM_SIZE_TEAR)},
    {"sortTensorByDimKey", dim3(GRID_SIZE_SORT_TENSOR_BY_DIM_KEY, BLOCK_SIZE_SORT_TENSOR_BY_DIM_KEY, SHARED_MEM_SIZE_SORT_TENSOR_BY_DIM_KEY)},
    {"sortTensorAlongDimKey", dim3(GRID_SIZE_SORT_TENSOR_ALONG_DIM_KEY, BLOCK_SIZE_SORT_TENSOR_ALONG_DIM_KEY, SHARED_MEM_SIZE_SORT_TENSOR_ALONG_DIM_KEY)},
    {"sortTensorAlongDimValue", dim3(GRID_SIZE_SORT_TENSOR_ALONG_DIM_VALUE, BLOCK_SIZE_SORT_TENSOR_ALONG_DIM_VALUE, SHARED_MEM_SIZE_SORT_TENSOR_ALONG_DIM_VALUE)},
    {"shuffle", dim3(GRID_SIZE_SHUFFLE, BLOCK_SIZE_SHUFFLE, SHARED_MEM_SIZE_SHUFFLE)},
    {"pullRows", dim3(GRID_SIZE_PULLROWS, BLOCK_SIZE_PULLROWS, SHARED_MEM_SIZE_PULLROWS)},
    {"prescanArrayRecursive", dim3(GRID_SIZE_PRESCAN_ARRAY_RECURSIVE, BLOCK_SIZE_PRESCAN_ARRAY_RECURSIVE, SHARED_MEM_SIZE_PRESCAN_ARRAY_RECURSIVE)},
    {"scalarTad", dim3(GRID_SIZE_SCALAR_TAD, BLOCK_SIZE_SCALAR_TAD, SHARED_MEM_SIZE_SCALAR_TAD)},
    {"scalarScan", dim3(GRID_SIZE_SCALAR_SCAN, BLOCK_SIZE_SCALAR_SCAN, SHARED_MEM_SIZE_SCALAR_SCAN)},
    {"reduceLong", dim3(GRID_SIZE_REDUCE_LONG, BLOCK_SIZE_REDUCE_LONG, SHARED_MEM_SIZE_REDUCE_LONG)},
    {"reduceBool", dim3(GRID_SIZE_REDUCE_BOOL, BLOCK_SIZE_REDUCE_BOOL, SHARED_MEM_SIZE_REDUCE_BOOL)},
    {"average", dim3(GRID_SIZE_AVERAGE, BLOCK_SIZE_AVERAGE, SHARED_MEM_SIZE_AVERAGE)},
    {"accumulate", dim3(GRID_SIZE_ACCUMULATE, BLOCK_SIZE_ACCUMULATE, SHARED_MEM_SIZE_ACCUMULATE)},
    {"transformScan", dim3(GRID_SIZE_TRANSFORM_SCAN, BLOCK_SIZE_TRANSFORM_SCAN, SHARED_MEM_SIZE_TRANSFORM_SCAN)},
    {"summaryStats", dim3(GRID_SIZE_SUMMARY_STATS, BLOCK_SIZE_SUMMARY_STATS, SHARED_MEM_SIZE_SUMMARY_STATS)},
    {"reduceFloat", dim3(GRID_SIZE_REDUCE_FLOAT, BLOCK_SIZE_REDUCE_FLOAT, SHARED_MEM_SIZE_REDUCE_FLOAT)},
    {"scalarBool", dim3(GRID_SIZE_SCALAR_BOOL, BLOCK_SIZE_SCALAR_BOOL, SHARED_MEM_SIZE_SCALAR_BOOL)},
    {"scalarSame", dim3(GRID_SIZE_SCALAR_SAME, BLOCK_SIZE_SCALAR_SAME, SHARED_MEM_SIZE_SCALAR_SAME)},
    {"scalarLong", dim3(GRID_SIZE_SCALAR_LONG, BLOCK_SIZE_SCALAR_LONG, SHARED_MEM_SIZE_SCALAR_LONG)},
    {"reduce3", dim3(GRID_SIZE_REDUCE_3, BLOCK_SIZE_REDUCE_3, SHARED_MEM_SIZE_REDUCE_3)},
    {"pairwiseTransforms", dim3(GRID_SIZE_PAIRWISE_TRANSFORMS, BLOCK_SIZE_PAIRWISE_TRANSFORMS, SHARED_MEM_SIZE_PAIRWISE_TRANSFORMS)},
    {"broadcast", dim3(GRID_SIZE_BROADCAST, BLOCK_SIZE_BROADCAST, SHARED_MEM_SIZE_BROADCAST)},
    {"broadcastInt", dim3(GRID_SIZE_BROADCAST_INT, BLOCK_SIZE_BROADCAST_INT, SHARED_MEM_SIZE_BROADCAST_INT)},
    {"broadcastBool", dim3(GRID_SIZE_BROADCAST_BOOL, BLOCK_SIZE_BROADCAST_BOOL, SHARED_MEM_SIZE_BROADCAST_BOOL)},
    {"matrixMultiply", dim3(GRID_SIZE_MATRIX_MULTIPLY, BLOCK_SIZE_MATRIX_MULTIPLY, SHARED_MEM_SIZE_MATRIX_MULTIPLY)},
    {"im2col", {dim3(GRID_SIZE_IM2COL, BLOCK_SIZE_IM2COL, SHARED_MEM_SIZE_IM2COL)}},
    {"col2im", {dim3(GRID_SIZE_COL2IM, BLOCK_SIZE_COL2IM, SHARED_MEM_SIZE_COL2IM)}},
    {"gemv", {dim3(GRID_SIZE_GEMV, BLOCK_SIZE_GEMV, SHARED_MEM_SIZE_GEMV)}},
    {"addBias", {dim3(GRID_SIZE_ADDBIAS, BLOCK_SIZE_ADDBIAS, SHARED_MEM_SIZE_ADDBIAS)}},
    {"pooling", {dim3(GRID_SIZE_POOLING, BLOCK_SIZE_POOLING, SHARED_MEM_SIZE_POOLING)}},
    {"vol2col", {dim3(GRID_SIZE_VOL2COL, BLOCK_SIZE_VOL2COL, SHARED_MEM_SIZE_VOL2COL)}},
    {"col2vol", {dim3(GRID_SIZE_COL2VOL, BLOCK_SIZE_COL2VOL, SHARED_MEM_SIZE_COL2VOL)}},
    {"upsampling", {dim3(GRID_SIZE_UPSAMPLING, BLOCK_SIZE_UPSAMPLING, SHARED_MEM_SIZE_UPSAMPLING)}},
    {"histogram", {dim3(GRID_SIZE_HISTOGRAM, BLOCK_SIZE_HISTOGRAM, SHARED_MEM_SIZE_HISTOGRAM)}},
    {"prelu", {dim3(GRID_SIZE_PRELU, BLOCK_SIZE_PRELU, SHARED_MEM_SIZE_PRELU)}},
    {"adjust", {dim3(GRID_SIZE_ADJUST, BLOCK_SIZE_ADJUST, SHARED_MEM_SIZE_ADJUST)}},
    {"compare_and_bitpack", {dim3(GRID_SIZE_COMPARE_AND_BITPACK, BLOCK_SIZE_COMPARE_AND_BITPACK, SHARED_MEM_SIZE_COMPARE_AND_BITPACK)}},
    {"concat", {dim3(GRID_SIZE_CONCAT, BLOCK_SIZE_CONCAT, SHARED_MEM_SIZE_CONCAT)}},
    {"confusion_matrix", {dim3(GRID_SIZE_CONFUSION_MATRIX, BLOCK_SIZE_CONFUSION_MATRIX, SHARED_MEM_SIZE_CONFUSION_MATRIX)}},
    {"beta_inc", {dim3(GRID_SIZE_BETA_INC, BLOCK_SIZE_BETA_INC, SHARED_MEM_SIZE_BETA_INC)}},
    {"clip", {dim3(GRID_SIZE_CLIP, BLOCK_SIZE_CLIP, SHARED_MEM_SIZE_CLIP)}},
    {"cross", {dim3(GRID_SIZE_CROSS, BLOCK_SIZE_CROSS, SHARED_MEM_SIZE_CROSS)}},
    {"depth_to_space", {dim3(GRID_SIZE_DEPTH_TO_SPACE, BLOCK_SIZE_DEPTH_TO_SPACE, SHARED_MEM_SIZE_DEPTH_TO_SPACE)}},
    {"dilation", {dim3(GRID_SIZE_DILATION, BLOCK_SIZE_DILATION, SHARED_MEM_SIZE_DILATION)}},
    {"dropout", {dim3(GRID_SIZE_DROPOUT, BLOCK_SIZE_DROPOUT, SHARED_MEM_SIZE_DROPOUT)}},
    {"extract_patches", {dim3(GRID_SIZE_EXTRACT_PATCHES, BLOCK_SIZE_EXTRACT_PATCHES, BLOCK_SIZE_EXTRACT_PATCHES)}},
    {"fake_quantization", {dim3(GRID_SIZE_FAKE_QUANTIZATION, BLOCK_SIZE_FAKE_QUANTIZATION, SHARED_MEM_SIZE_FAKE_QUANTIZATION)}},
    {"flatten", {dim3(GRID_SIZE_FLATTEN, BLOCK_SIZE_FLATTEN, SHARED_MEM_SIZE_FLATTEN)}},
    {"gather", {dim3(GRID_SIZE_GATHER, BLOCK_SIZE_GATHER, SHARED_MEM_SIZE_GATHER)}},
    {"gather_linear", {dim3(GRID_SIZE_GATHER_LINEAR, BLOCK_SIZE_GATHER_LINEAR, SHARED_MEM_SIZE_GATHER_LINEAR)}},
    {"gather_nd", {dim3(GRID_SIZE_GATHERND, BLOCK_SIZE_GATHERND, SHARED_MEM_SIZE_GATHERND)}},
    {"hamming", {dim3(GRID_SIZE_HAMMING, BLOCK_SIZE_HAMMING, SHARED_MEM_SIZE_HAMMING)}},
    {"hashcode_split", {dim3(GRID_SIZE_HASHCODE_SPLIT, BLOCK_SIZE_HASHCODE_SPLIT, SHARED_MEM_SIZE_HASHCODE_SPLIT)}},
    {"hashcode_internal", {dim3(GRID_SIZE_HASHCODE_INTERNAL, BLOCK_SIZE_HASHCODE_INTERNAL, SHARED_MEM_SIZE_HASHCODE_INTERNAL)}},
    {"hashcode_last", {dim3(GRID_SIZE_HASHCODE_LAST, BLOCK_SIZE_HASHCODE_LAST, SHARED_MEM_SIZE_HASHCODE_LAST)}},
    {"histogram_fixed_width", {dim3(GRID_SIZE_HISTOGRAM_FIXED_WIDTH, BLOCK_SIZE_HISTOGRAM_FIXED_WIDTH, SHARED_MEM_SIZE_HISTOGRAM_FIXED_WIDTH)}},
    {"draw_bounding_boxes", {dim3(GRID_SIZE_DRAW_BOUNDING_BOXES, BLOCK_SIZE_DRAW_BOUNDING_BOXES, SHARED_MEM_SIZE_DRAW_BOUNDING_BOXES)}},
    {"image_resize", {dim3(GRID_SIZE_IMAGE_RESIZE, BLOCK_SIZE_IMAGE_RESIZE, SHARED_MEM_SIZE_IMAGE_RESIZE)}},
    {"image_resize_interp_weights", {dim3(GRID_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS, BLOCK_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS, SHARED_MEM_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS)}},
    {"image_resize_init_coeffs", {dim3(GRID_SIZE_IMAGE_RESIZE_INIT_COEFFS, BLOCK_SIZE_IMAGE_RESIZE_INIT_COEFFS, SHARED_MEM_SIZE_IMAGE_RESIZE_INIT_COEFFS)}},
    {"image_resize_coeffs_accum", {dim3(GRID_SIZE_IMAGE_RESIZE_COEFFS_ACCUM, BLOCK_SIZE_IMAGE_RESIZE_COEFFS_ACCUM, SHARED_MEM_SIZE_IMAGE_RESIZE_COEFFS_ACCUM)}},
    {"image_resize_bicubic", {dim3(GRID_SIZE_IMAGE_RESIZE_BICUBIC, BLOCK_SIZE_IMAGE_RESIZE_BICUBIC, SHARED_MEM_SIZE_IMAGE_RESIZE_BICUBIC)}},
    {"image_resize_fill_interp", {dim3(GRID_SIZE_IMAGE_RESIZE_FILL_INTERP, BLOCK_SIZE_IMAGE_RESIZE_FILL_INTERP, SHARED_MEM_SIZE_IMAGE_RESIZE_FILL_INTERP)}},
    {"image_resize_crop_and_resize", {dim3(GRID_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE, BLOCK_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE, SHARED_MEM_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE)}},
    {"image_resize_v2_gather", {dim3(GRID_SIZE_IMAGE_RESIZE_V2_GATHER, BLOCK_SIZE_IMAGE_RESIZE_V2_GATHER, SHARED_MEM_SIZE_IMAGE_RESIZE_V2_GATHER)}},
    {"image_suppress_scores", {dim3(GRID_SIZE_IMAGE_SUPPRESS_SCORES, BLOCK_SIZE_IMAGE_SUPPRESS_SCORES, SHARED_MEM_SIZE_IMAGE_SUPPRESS_SCORES)}},
    {"image_suppress_select", {dim3(GRID_SIZE_IMAGE_SUPPRESS_SELECT, BLOCK_SIZE_IMAGE_SUPPRESS_SELECT, SHARED_MEM_SIZE_IMAGE_SUPPRESS_SELECT)}},
    {"image_suppress_nonmax_overlap", {dim3(GRID_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP, BLOCK_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP, SHARED_MEM_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP)}},
    {"image_helpers_triple", {dim3(GRID_SIZE_IMAGE_HELPERS_TRIPLE, BLOCK_SIZE_IMAGE_HELPERS_TRIPLE, SHARED_MEM_SIZE_IMAGE_HELPERS_TRIPLE)}},
    {"image_helpers", {dim3(GRID_SIZE_IMAGE_HELPERS, BLOCK_SIZE_IMAGE_HELPERS, SHARED_MEM_SIZE_GRID_SIZE_IMAGE_HELPERS)}},
    {"lrn", {dim3(GRID_SIZE_LRN, BLOCK_SIZE_LRN, SHARED_MEM_SIZE_LRN)}},
    {"lstsq_reg", {dim3(GRID_SIZE_LSTSQ_REG, BLOCK_SIZE_LSTSQ_REG, SHARED_MEM_SIZE_LSTSQ_REG)}},
    {"lup", {dim3(GRID_SIZE_LUP, GRID_SIZE_LUP, SHARED_MEM_SIZE_LUP)}},
    {"lup_low", {dim3(GRID_SIZE_LUP_LOW, BLOCK_SIZE_LUP_LOW, SHARED_MEM_SIZE_LUP_LOW)}},
    {"matrix_set_diag", {dim3(GRID_SIZE_MATRIX_SET_DIAG, BLOCK_SIZE_MATRIX_SET_DIAG, SHARED_MEM_SIZE_MATRIX_SET_DIAG)}},
    {"merge", {dim3(GRID_SIZE_MERGE, BLOCK_SIZE_MERGE, SHARED_MEM_SIZE_MERGE)}},
    {"meshgrid", {dim3(GRID_SIZE_MESHGRID, BLOCK_SIZE_MESHGRID, SHARED_MEM_SIZE_MESHGRID)}},
    {"nth_element_fill", {dim3(GRID_SIZE_NTH_ELEMENT_FILL, BLOCK_SIZE_NTH_ELEMENT_FILL, SHARED_MEM_SIZE_NTH_ELEMENT_FILL)}},
    {"one_hot", {dim3(GRID_SIZE_ONE_HOT, BLOCK_SIZE_ONE_HOT, SHARED_MEM_SIZE_ONE_HOT)}},
    {"pad", {dim3(GRID_SIZE_PAD, BLOCK_SIZE_PAD, SHARED_MEM_SIZE_PAD)}},
    {"percentile", {dim3(GRID_SIZE_PERCENTILE, BLOCK_SIZE_PERCENTILE, SHARED_MEM_SIZE_PERCENTILE)}},
    {"polygamma", {dim3(GRID_SIZE_POLYGAMMA, BLOCK_SIZE_POLYGAMMA, SHARED_MEM_SIZE_POLYGAMMA)}},
    {"prefix", {dim3(GRID_SIZE_PREFIX, BLOCK_SIZE_PREFIX, SHARED_MEM_SIZE_PREFIX)}},
    {"print", {dim3(GRID_SIZE_PRINT, BLOCK_SIZE_PRINT, SHARED_MEM_SIZE_PRINT)}},
    {"qr", {dim3(GRID_SIZE_QR, BLOCK_SIZE_QR, SHARED_MEM_SIZE_QR)}},
    {"random_gamma", {dim3(GRID_SIZE_RANDOM_GAMMA, BLOCK_SIZE_RANDOM_GAMMA, SHARED_MEM_SIZE_RANDOM_GAMMA)}},
    {"random_poisson", {dim3(GRID_SIZE_RANDOM_POISSON, BLOCK_SIZE_RANDOM_POISSON, SHARED_MEM_SIZE_RANDOM_POISSON)}},
    {"random_uniform", {dim3(GRID_SIZE_RANDOM_UNIFORM, BLOCK_SIZE_RANDOM_UNIFORM, SHARED_MEM_SIZE_RANDOM_UNIFORM)}},
    {"random_shuffle_fisher", {dim3(GRID_SIZE_RANDOM_SHUFFLE_FISHER, BLOCK_SIZE_RANDOM_SHUFFLE_FISHER, SHARED_MEM_SIZE_RANDOM_SHUFFLE_FISHER)}},
    {"range", {dim3(GRID_SIZE_RANGE, BLOCK_SIZE_RANGE, SHARED_MEM_SIZE_RANGE)}},
    {"reverse", {dim3(GRID_SIZE_REVERSE, BLOCK_SIZE_REVERSE, SHARED_MEM_SIZE_REVERSE)}},
    {"roll", {dim3(GRID_SIZE_ROLL, BLOCK_SIZE_ROLL, SHARED_MEM_SIZE_ROLL)}},
    {"batch_to_space_nd", {dim3(GRID_SIZE_BATCH_TO_SPACE_ND, BLOCK_SIZE_BATCH_TO_SPACE_ND, SHARED_MEM_SIZE_BATCH_TO_SPACE_ND)}},
    {"space_to_batch", {dim3(GRID_SIZE_SPACE_TO_BATCH, BLOCK_SIZE_SPACE_TO_BATCH, SHARED_MEM_SIZE_SPACE_TO_BATCH)}},
    {"space_to_batch_nd", {dim3(GRID_SIZE_SPACE_TO_BATCH_ND, BLOCK_SIZE_SPACE_TO_BATCH_ND, SHARED_MEM_SIZE_SPACE_TO_BATCH_ND)}},
    {"space_to_depth", {dim3(GRID_SIZE_SPACE_TO_DEPTH, BLOCK_SIZE_SPACE_TO_DEPTH, SHARED_MEM_SIZE_SPACE_TO_DEPTH)}},
    {"scatter", {dim3(GRID_SIZE_SCATTER, BLOCK_SIZE_SCATTER, SHARED_MEM_SIZE_SCATTER)}},
    {"scatter_check_indices", {dim3(GRID_SIZE_SCATTER_CHECK_INDICES, BLOCK_SIZE_SCATTER_CHECK_INDICES, SHARED_MEM_SIZE_SCATTER_CHECK_INDICES)}},
    {"scatter_nd", {dim3(GRID_SIZE_SCATTER_ND, BLOCK_SIZE_SCATTER_ND, SHARED_MEM_SIZE_SCATTER_ND)}},
    {"scatter_simple", {dim3(GRID_SIZE_SCATTER_SIMPLE, BLOCK_SIZE_SCATTER_SIMPLE, SHARED_MEM_SIZE_SCATTER_SIMPLE)}},
    {"scatter_update", {dim3(GRID_SIZE_SCATTER_UPDATE, BLOCK_SIZE_SCATTER_UPDATE, SHARED_MEM_SIZE_SCATTER_UPDATE)}},
    {"segment_indices", {dim3(GRID_SIZE_SEGMENT_INDICES_VALIDATE, BLOCK_SIZE_SEGMENT_INDICES_VALIDATE, SHARED_MEM_SIZE_SEGMENT_INDICES_VALIDATE)}},
    {"segment", {dim3(GRID_SIZE_SEGMENT, BLOCK_SIZE_SEGMENT, SHARED_MEM_SIZE_SEGMENT)}},
    {"segment_tad", {dim3(GRID_SIZE_SEGMENT_TAD, BLOCK_SIZE_SEGMENT_TAD, SHARED_MEM_SIZE_SEGMENT_TAD)}},
    {"unsorted_segment_prod_2", {dim3(GRID_SIZE_UNSORTEDSEGMENT_PROD_2, BLOCK_SIZE_UNSORTEDSEGMENT_PROD_2, SHARED_MEM_SIZE_UNSORTEDSEGMENT_PROD_2)}},
    {"solve", {dim3(GRID_SIZE_SOLVE, BLOCK_SIZE_SOLVE, SHARED_MEM_SIZE_SOLVE)}},
    {"sru_bi", {dim3(GRID_SIZE_SRU_BI, BLOCK_SIZE_SRU_BI, SHARED_MEM_SIZE_SRU_BI)}},


};

std::unordered_map<std::string, std::vector<std::string>> algoDimMapString = {
    {"random", {"GRID_SIZE_RANDOM", "BLOCK_SIZE_RANDOM", "SHARED_MEM_SIZE_RANDOM"}},
    {"diagPart", {"GRID_SIZE_DIAG_PART", "BLOCK_SIZE_DIAG_PART", "SHARED_MEM_SIZE_DIAG_PART"}},
    {"logAbsDeterminant", {"GRID_SIZE_LOG_ABS_DETERMINANT", "BLOCK_SIZE_LOG_ABS_DETERMINANT", "SHARED_MEM_SIZE_LOG_ABS_DETERMINANT"}},
    {"adjustWeights", {"GRID_SIZE_ADJUST_WEIGHTS", "BLOCK_SIZE_ADJUST_WEIGHTS", "SHARED_MEM_SIZE_ADJUST_WEIGHTS"}},
    {"sequenceMask", {"GRID_SIZE_SEQUENCE_MASK", "BLOCK_SIZE_SEQUENCE_MASK", "SHARED_MEM_SIZE_SEQUENCE_MASK"}},
    {"segmentSum", {"GRID_SIZE_SEGMENT_SUM", "BLOCK_SIZE_SEGMENT_SUM", "SHARED_MEM_SIZE_SEGMENT_SUM"}},
    {"unsortedSegmentSum", {"GRID_SIZE_UNSORTED_SEGMENT_SUM", "BLOCK_SIZE_UNSORTED_SEGMENT_SUM", "SHARED_MEM_SIZE_UNSORTED_SEGMENT_SUM"}},
    {"segmentSqrtN", {"GRID_SIZE_SEGMENT_SQRTN", "BLOCK_SIZE_SEGMENT_SQRTN", "SHARED_MEM_SIZE_SEGMENT_SQRTN"}},
    {"segmentProd", {"GRID_SIZE_SEGMENT_PROD", "BLOCK_SIZE_SEGMENT_PROD", "SHARED_MEM_SIZE_SEGMENT_PROD"}},
    {"unsortedSegmentProd", {"GRID_SIZE_UNSORTED_SEGMENT_PROD", "BLOCK_SIZE_UNSORTED_SEGMENT_PROD", "SHARED_MEM_SIZE_UNSORTED_SEGMENT_PROD"}},
    {"segmentMin", {"GRID_SIZE_SEGMENT_MIN", "BLOCK_SIZE_SEGMENT_MIN", "SHARED_MEM_SIZE_SEGMENT_MIN"}},
    {"unsortedSegmentMin", {"GRID_SIZE_UNSORTED_SEGMENT_MIN", "BLOCK_SIZE_UNSORTED_SEGMENT_MIN", "SHARED_MEM_SIZE_UNSORTED_SEGMENT_MIN"}},
    {"segmentMean", {"GRID_SIZE_SEGMENT_MEAN", "BLOCK_SIZE_SEGMENT_MEAN", "SHARED_MEM_SIZE_SEGMENT_MEAN"}},
    {"unsortedSegmentMean", {"GRID_SIZE_UNSORTED_SEGMENT_MEAN", "BLOCK_SIZE_UNSORTED_SEGMENT_MEAN", "SHARED_MEM_SIZE_UNSORTED_SEGMENT_MEAN"}},
    {"segmentMax", {"GRID_SIZE_SEGMENT_MAX", "BLOCK_SIZE_SEGMENT_MAX", "SHARED_MEM_SIZE_SEGMENT_MAX"}},
    {"unsortedSegmentMax", {"GRID_SIZE_UNSORTED_SEGMENT_MAX", "BLOCK_SIZE_UNSORTED_SEGMENT_MAX", "SHARED_MEM_SIZE_UNSORTED_SEGMENT_MAX"}},
    {"matrixDiag", {"GRID_SIZE_MATRIX_DIAG", "BLOCK_SIZE_MATRIX_DIAG", "SHARED_MEM_SIZE_MATRIX_DIAG"}},
    {"segmentFillUpSegments", {"GRID_SIZE_SEGMENT_FILL_UP_SEGMENTS", "BLOCK_SIZE_SEGMENT_FILL_UP_SEGMENTS", "SHARED_MEM_SIZE_SEGMENT_FILL_UP_SEGMENTS"}},
    {"matrixBand", {"GRID_SIZE_MATRIX_BAND", "BLOCK_SIZE_MATRIX_BAND", "SHARED_MEM_SIZE_MATRIX_BAND"}},
    {"lup", {"GRID_SIZE_LUP", "BLOCK_SIZE_LUP", "SHARED_MEM_SIZE_LUP"}},
    {"ismax", {"GRID_SIZE_ISMAX", "BLOCK_SIZE_ISMAX", "SHARED_MEM_SIZE_ISMAX"}},
    {"ismaxFill", {"GRID_SIZE_ISMAX_FILL", "BLOCK_SIZE_ISMAX_FILL", "SHARED_MEM_SIZE_ISMAX_FILL"}},
    {"imageResize", {"GRID_SIZE_IMAGE_RESIZE", "BLOCK_SIZE_IMAGE_RESIZE", "SHARED_MEM_SIZE_IMAGE_RESIZE"}},
    {"diag", {"GRID_SIZE_DIAG", "BLOCK_SIZE_DIAG", "SHARED_MEM_SIZE_DIAG"}},
    {"confusionMatrix", {"GRID_SIZE_CONFUSION_MATRIX", "BLOCK_SIZE_CONFUSION_MATRIX", "SHARED_MEM_SIZE_CONFUSION_MATRIX"}},
    {"tile", {"GRID_SIZE_TILE", "BLOCK_SIZE_TILE", "SHARED_MEM_SIZE_TILE"}},
    {"diagonal", {"GRID_SIZE_DIAGONAL", "BLOCK_SIZE_DIAGONAL", "SHARED_MEM_SIZE_DIAGONAL"}},
    {"tear", {"GRID_SIZE_TEAR", "BLOCK_SIZE_TEAR", "SHARED_MEM_SIZE_TEAR"}},
    {"sortTensorByDimKey", {"GRID_SIZE_SORT_TENSOR_BY_DIM_KEY", "BLOCK_SIZE_SORT_TENSOR_BY_DIM_KEY", "SHARED_MEM_SIZE_SORT_TENSOR_BY_DIM_KEY"}},
    {"sortTensorAlongDimKey", {"GRID_SIZE_SORT_TENSOR_ALONG_DIM_KEY", "BLOCK_SIZE_SORT_TENSOR_ALONG_DIM_KEY", "SHARED_MEM_SIZE_SORT_TENSOR_ALONG_DIM_KEY"}},
    {"sortTensorAlongDimValue", {"GRID_SIZE_SORT_TENSOR_ALONG_DIM_VALUE", "BLOCK_SIZE_SORT_TENSOR_ALONG_DIM_VALUE", "SHARED_MEM_SIZE_SORT_TENSOR_ALONG_DIM_VALUE"}},
    {"shuffle", {"GRID_SIZE_SHUFFLE", "BLOCK_SIZE_SHUFFLE", "SHARED_MEM_SIZE_SHUFFLE"}},
    {"pullRows", {"GRID_SIZE_PULLROWS", "BLOCK_SIZE_PULLROWS", "SHARED_MEM_SIZE_PULLROWS"}},
    {"prescanArrayRecursive", {"GRID_SIZE_PRESCAN_ARRAY_RECURSIVE", "BLOCK_SIZE_PRESCAN_ARRAY_RECURSIVE", "SHARED_MEM_SIZE_PRESCAN_ARRAY_RECURSIVE"}},
    {"scalarTad", {"GRID_SIZE_SCALAR_TAD", "BLOCK_SIZE_SCALAR_TAD", "SHARED_MEM_SIZE_SCALAR_TAD"}},
    {"scalarScan", {"GRID_SIZE_SCALAR_SCAN", "BLOCK_SIZE_SCALAR_SCAN", "SHARED_MEM_SIZE_SCALAR_SCAN"}},
    {"reduceLong", {"GRID_SIZE_REDUCE_LONG", "BLOCK_SIZE_REDUCE_LONG", "SHARED_MEM_SIZE_REDUCE_LONG"}},
    {"reduceBool", {"GRID_SIZE_REDUCE_BOOL", "BLOCK_SIZE_REDUCE_BOOL", "SHARED_MEM_SIZE_REDUCE_BOOL"}},
    {"average", {"GRID_SIZE_AVERAGE", "BLOCK_SIZE_AVERAGE", "SHARED_MEM_SIZE_AVERAGE"}},
    {"accumulate", {"GRID_SIZE_ACCUMULATE", "BLOCK_SIZE_ACCUMULATE", "SHARED_MEM_SIZE_ACCUMULATE"}},
    {"transformScan", {"GRID_SIZE_TRANSFORM_SCAN", "BLOCK_SIZE_TRANSFORM_SCAN", "SHARED_MEM_SIZE_TRANSFORM_SCAN"}},
    {"summaryStats", {"GRID_SIZE_SUMMARY_STATS", "BLOCK_SIZE_SUMMARY_STATS", "SHARED_MEM_SIZE_SUMMARY_STATS"}},
    {"reduceFloat", {"GRID_SIZE_REDUCE_FLOAT", "BLOCK_SIZE_REDUCE_FLOAT", "SHARED_MEM_SIZE_REDUCE_FLOAT"}},
    {"scalarBool", {"GRID_SIZE_SCALAR_BOOL", "BLOCK_SIZE_SCALAR_BOOL", "SHARED_MEM_SIZE_SCALAR_BOOL"}},
    {"scalarSame", {"GRID_SIZE_SCALAR_SAME", "BLOCK_SIZE_SCALAR_SAME", "SHARED_MEM_SIZE_SCALAR_SAME"}},
    {"scalarLong", {"GRID_SIZE_SCALAR_LONG", "BLOCK_SIZE_SCALAR_LONG", "SHARED_MEM_SIZE_SCALAR_LONG"}},
    {"reduce3", {"GRID_SIZE_REDUCE_3", "BLOCK_SIZE_REDUCE_3", "SHARED_MEM_SIZE_REDUCE_3"}},
    {"pairwiseTransforms", {"GRID_SIZE_PAIRWISE_TRANSFORMS", "BLOCK_SIZE_PAIRWISE_TRANSFORMS", "SHARED_MEM_SIZE_PAIRWISE_TRANSFORMS"}},
    {"broadcast", {"GRID_SIZE_BROADCAST", "BLOCK_SIZE_BROADCAST", "SHARED_MEM_SIZE_BROADCAST"}},
    {"broadcastInt", {"GRID_SIZE_BROADCAST_INT", "BLOCK_SIZE_BROADCAST_INT", "SHARED_MEM_SIZE_BROADCAST_INT"}},
    {"broadcastBool", {"GRID_SIZE_BROADCAST_BOOL", "BLOCK_SIZE_BROADCAST_BOOL", "SHARED_MEM_SIZE_BROADCAST_BOOL"}},
    {"matrixMultiply", {"GRID_SIZE_MATRIX_MULTIPLY", "BLOCK_SIZE_MATRIX_MULTIPLY", "SHARED_MEM_SIZE_MATRIX_MULTIPLY"}},
    {"im2col", {"GRID_SIZE_IM2COL", "BLOCK_SIZE_IM2COL", "SHARED_MEM_SIZE_IM2COL"}},
    {"col2im", {"GRID_SIZE_COL2IM", "BLOCK_SIZE_COL2IM", "SHARED_MEM_SIZE_COL2IM"}},
    {"gemv", {"GRID_SIZE_GEMV", "BLOCK_SIZE_GEMV", "SHARED_MEM_SIZE_GEMV"}},
    {"addBias", {"GRID_SIZE_ADDBIAS", "BLOCK_SIZE_ADDBIAS", "SHARED_MEM_SIZE_ADDBIAS"}},
    {"pooling", {"GRID_SIZE_POOLING", "BLOCK_SIZE_POOLING", "SHARED_MEM_SIZE_POOLING"}},
    {"vol2col", {"GRID_SIZE_VOL2COL", "BLOCK_SIZE_VOL2COL", "SHARED_MEM_SIZE_VOL2COL"}},
    {"col2vol", {"GRID_SIZE_COL2VOL", "BLOCK_SIZE_COL2VOL", "SHARED_MEM_SIZE_COL2VOL"}},
    {"upsampling", {"GRID_SIZE_UPSAMPLING", "BLOCK_SIZE_UPSAMPLING", "SHARED_MEM_SIZE_UPSAMPLING"}},
    {"histogram", {"GRID_SIZE_HISTOGRAM", "BLOCK_SIZE_HISTOGRAM", "SHARED_MEM_SIZE_HISTOGRAM"}},
    {"prelu", {"GRID_SIZE_PRELU", "BLOCK_SIZE_PRELU", "SHARED_MEM_SIZE_PRELU"}},
    {"adjust", {"GRID_SIZE_ADJUST", "BLOCK_SIZE_ADJUST", "SHARED_MEM_SIZE_ADJUST"}},
    {"compare_and_bitpack", {"GRID_SIZE_COMPARE_AND_BITPACK", "BLOCK_SIZE_COMPARE_AND_BITPACK", "SHARED_MEM_SIZE_COMPARE_AND_BITPACK"}},
    {"concat", {"GRID_SIZE_CONCAT", "BLOCK_SIZE_CONCAT", "SHARED_MEM_SIZE_CONCAT"}},
    {"confusion_matrix", {"GRID_SIZE_CONFUSION_MATRIX", "BLOCK_SIZE_CONFUSION_MATRIX", "SHARED_MEM_SIZE_CONFUSION_MATRIX"}},
    {"beta_inc", {"GRID_SIZE_BETA_INC", "BLOCK_SIZE_BETA_INC", "SHARED_MEM_SIZE_BETA_INC"}},
    {"clip", {"GRID_SIZE_CLIP", "BLOCK_SIZE_CLIP", "SHARED_MEM_SIZE_CLIP"}},
    {"cross", {"GRID_SIZE_CROSS", "BLOCK_SIZE_CROSS", "SHARED_MEM_SIZE_CROSS"}},
    {"depth_to_space", {"GRID_SIZE_DEPTH_TO_SPACE", "BLOCK_SIZE_DEPTH_TO_SPACE", "SHARED_MEM_SIZE_DEPTH_TO_SPACE"}},
    {"dilation", {"GRID_SIZE_DILATION", "BLOCK_SIZE_DILATION", "SHARED_MEM_SIZE_DILATION"}},
    {"dropout", {"GRID_SIZE_DROPOUT", "BLOCK_SIZE_DROPOUT", "SHARED_MEM_SIZE_DROPOUT"}},
    {"fake_quantization", {"GRID_SIZE_FAKE_QUANTIZATION", "BLOCK_SIZE_FAKE_QUANTIZATION", "SHARED_MEM_SIZE_FAKE_QUANTIZATION"}},
    {"flatten", {"GRID_SIZE_FLATTEN", "BLOCK_SIZE_FLATTEN", "SHARED_MEM_SIZE_FLATTEN"}},
    {"gather_linear", {"GRID_SIZE_GATHER_LINEAR", "BLOCK_SIZE_GATHER_LINEAR", "SHARED_MEM_SIZE_GATHER_LINEAR"}},
    {"gather", {"GRID_SIZE_GATHER", "BLOCK_SIZE_GATHER", "SHARED_MEM_SIZE_GATHER"}},
    {"gather_nd", {"GRID_SIZE_GATHERND", "BLOCK_SIZE_GATHERND", "SHARED_MEM_SIZE_GATHERND"}},
    {"hamming", {"GRID_SIZE_HAMMING", "BLOCK_SIZE_HAMMING", "SHARED_MEM_SIZE_HAMMING"}},
    {"hashcode_split", {"GRID_SIZE_HASHCODE_SPLIT", "BLOCK_SIZE_HASHCODE_SPLIT", "SHARED_MEM_SIZE_HASHCODE_SPLIT"}},
    {"hashcode_internal", {"GRID_SIZE_HASHCODE_INTERNAL", "BLOCK_SIZE_HASHCODE_INTERNAL", "SHARED_MEM_SIZE_HASHCODE_INTERNAL"}},
    {"hashcode_last", {"GRID_SIZE_HASHCODE_LAST", "BLOCK_SIZE_HASHCODE_LAST", "SHARED_MEM_SIZE_HASHCODE_LAST"}},
    {"histogram_fixed_width", {"GRID_SIZE_HISTOGRAM_FIXED_WIDTH", "BLOCK_SIZE_HISTOGRAM_FIXED_WIDTH", "SHARED_MEM_SIZE_HISTOGRAM_FIXED_WIDTH"}},
    {"draw_bounding_boxes", {"GRID_SIZE_DRAW_BOUNDING_BOXES", "BLOCK_SIZE_DRAW_BOUNDING_BOXES", "SHARED_MEM_SIZE_DRAW_BOUNDING_BOXES"}},
    {"image_resize", {"GRID_SIZE_IMAGE_RESIZE", "BLOCK_SIZE_IMAGE_RESIZE", "SHARED_MEM_SIZE_IMAGE_RESIZE"}},
    {"image_resize_interp_weights", {"GRID_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS", "BLOCK_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS", "SHARED_MEM_SIZE_IMAGE_RESIZE_INTERP_WEIGHTS"}},
    {"image_resize_init_coeffs", {"GRID_SIZE_IMAGE_RESIZE_INIT_COEFFS", "BLOCK_SIZE_IMAGE_RESIZE_INIT_COEFFS", "SHARED_MEM_SIZE_IMAGE_RESIZE_INIT_COEFFS"}},
    {"image_resize_coeffs_accum", {"GRID_SIZE_IMAGE_RESIZE_COEFFS_ACCUM", "BLOCK_SIZE_IMAGE_RESIZE_COEFFS_ACCUM", "SHARED_MEM_SIZE_IMAGE_RESIZE_COEFFS_ACCUM"}},
    {"image_resize_bicubic", {"GRID_SIZE_IMAGE_RESIZE_BICUBIC", "BLOCK_SIZE_IMAGE_RESIZE_BICUBIC", "SHARED_MEM_SIZE_IMAGE_RESIZE_BICUBIC"}},
    {"image_resize_fill_interp", {"GRID_SIZE_IMAGE_RESIZE_FILL_INTERP", "BLOCK_SIZE_IMAGE_RESIZE_FILL_INTERP", "SHARED_MEM_SIZE_IMAGE_RESIZE_FILL_INTERP"}},
    {"image_resize_crop_and_resize", {"GRID_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE", "BLOCK_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE", "SHARED_MEM_SIZE_IMAGE_RESIZE_CROP_AND_RESIZE"}},
    {"image_resize_v2_gather", {"GRID_SIZE_IMAGE_RESIZE_V2_GATHER", "BLOCK_SIZE_IMAGE_RESIZE_V2_GATHER", "SHARED_MEM_SIZE_IMAGE_RESIZE_V2_GATHER"}},
    {"image_suppress_scores", {"GRID_SIZE_IMAGE_SUPPRESS_SCORES", "BLOCK_SIZE_IMAGE_SUPPRESS_SCORES", "SHARED_MEM_SIZE_IMAGE_SUPPRESS_SCORES"}},
    {"image_suppress_select", {"GRID_SIZE_IMAGE_SUPPRESS_SELECT", "BLOCK_SIZE_IMAGE_SUPPRESS_SELECT", "SHARED_MEM_SIZE_IMAGE_SUPPRESS_SELECT"}},
    {"image_suppress_nonmax_overlap", {"GRID_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP", "BLOCK_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP", "SHARED_MEM_SIZE_IMAGE_SUPPRESS_NONMAX_OVERLAP"}},
    {"image_helpers_triple", {"GRID_SIZE_IMAGE_HELPERS_TRIPLE", "BLOCK_SIZE_IMAGE_HELPERS_TRIPLE", "SHARED_MEM_SIZE_IMAGE_HELPERS_TRIPLE"}},
    {"image_helpers", {"GRID_SIZE_IMAGE_HELPERS", "BLOCK_SIZE_IMAGE_HELPERS", "SHARED_MEM_SIZE_GRID_SIZE_IMAGE_HELPERS"}},
    {"lrn", {"GRID_SIZE_LRN", "BLOCK_SIZE_LRN", "SHARED_MEM_SIZE_LRN"}},
    {"lstsq_reg", {"GRID_SIZE_LSTSQ_REG", "BLOCK_SIZE_LSTSQ_REG", "SHARED_MEM_SIZE_LSTSQ_REG"}},
    {"lup", {"GRID_SIZE_LUP", "BLOCK_SIZE_LUP", "SHARED_MEM_SIZE_LUP"}},
    {"lup_low", {"GRID_SIZE_LUP_LOW", "BLOCK_SIZE_LUP_LOW", "SHARED_MEM_SIZE_LUP_LOW"}},
    {"matrix_set_diag", {"GRID_SIZE_MATRIX_SET_DIAG", "BLOCK_MATRIX_SET_DIAG", "SHARED_MEM_SIZE_MATRIX_SET_DIAG"}},
    {"merge", {"GRID_SIZE_MERGE", "BLOCK_SIZE_MERGE", "SHARED_MEM_SIZE_MERGE"}},
    {"meshgrid", {"GRID_SIZE_MESHGRID", "BLOCK_SIZE_MESHGRID", "SHARED_MEM_SIZE_MESHGRID"}},
    {"nth_element_fill", {"GRID_SIZE_NTH_ELEMENT_FILL", "BLOCK_SIZE_NTH_ELEMENT_FILL", "SHARED_MEM_SIZE_NTH_ELEMENT_FILL"}},
    {"one_hot", {"GRID_SIZE_ONE_HOT", "BLOCK_SIZE_ONE_HOT", "SHARED_MEM_SIZE_ONE_HOT"}},
    {"pad", {"GRID_SIZE_PAD", "BLOCK_SIZE_PAD", "SHARED_MEM_SIZE_PAD"}},
    {"percentile", {"GRID_SIZE_PERCENTILE", "BLOCK_SIZE_PERCENTILE", "SHARED_MEM_SIZE_PERCENTILE"}},
    {"polygamma", {"GRID_SIZE_POLYGAMMA", "BLOCK_SIZE_POLYGAMMA", "SHARED_MEM_SIZE_POLYGAMMA"}},
    {"prefix", {"GRID_SIZE_PREFIX", "BLOCK_SIZE_PREFIX", "SHARED_MEM_SIZE_PREFIX"}},
    {"print", {"GRID_SIZE_PRINT", "BLOCK_SIZE_PRINT", "SHARED_MEM_SIZE_PRINT"}},
    {"qr", {"GRID_SIZE_QR", "BLOCK_SIZE_QR", "SHARED_MEM_SIZE_QR"}},
    {"random_gamma", {"GRID_SIZE_RANDOM_GAMMA", "BLOCK_SIZE_RANDOM_GAMMA", "SHARED_MEM_SIZE_RANDOM_GAMMA"}},
    {"random_poisson", {"GRID_SIZE_RANDOM_POISSON", "BLOCK_SIZE_RANDOM_POISSON", "SHARED_MEM_SIZE_RANDOM_POISSON"}},
    {"random_uniform", {"GRID_SIZE_RANDOM_UNIFORM", "BLOCK_SIZE_RANDOM_UNIFORM", "SHARED_MEM_SIZE_RANDOM_UNIFORM"}},
    {"random_shuffle_fisher", {"GRID_SIZE_RANDOM_SHUFFLE_FISHER", "BLOCK_SIZE_RANDOM_SHUFFLE_FISHER", "SHARED_MEM_SIZE_RANDOM_SHUFFLE_FISHER"}},
    {"range", {"GRID_SIZE_RANGE", "BLOCK_SIZE_RANGE", "SHARED_MEM_SIZE_RANGE"}},
    {"reverse", {"GRID_SIZE_REVERSE", "BLOCK_SIZE_REVERSE", "SHARED_MEM_SIZE_REVERSE"}},
    {"roll", {"GRID_SIZE_ROLL", "BLOCK_SIZE_ROLL", "SHARED_MEM_SIZE_ROLL"}},
    {"batch_to_space_nd", {"GRID_SIZE_BATCH_TO_SPACE_ND", "BLOCK_SIZE_BATCH_TO_SPACE_ND", "SHARED_MEM_SIZE_BATCH_TO_SPACE_ND"}},
    {"space_to_batch", {"GRID_SIZE_SPACE_TO_BATCH", "BLOCK_SIZE_SPACE_TO_BATCH", "SHARED_MEM_SIZE_SPACE_TO_BATCH"}},
    {"space_to_batch_nd", {"GRID_SIZE_SPACE_TO_BATCH_ND", "BLOCK_SIZE_SPACE_TO_BATCH_ND", "SHARED_MEM_SIZE_SPACE_TO_BATCH_ND"}},
    {"space_to_depth", {"GRID_SIZE_SPACE_TO_DEPTH", "BLOCK_SIZE_SPACE_TO_DEPTH", "SHARED_MEM_SIZE_SPACE_TO_DEPTH"}},
    {"scatter", {"GRID_SIZE_SCATTER", "BLOCK_SIZE_SCATTER", "SHARED_MEM_SIZE_SCATTER"}},
    {"scatter_check_indices", {"GRID_SIZE_SCATTER_CHECK_INDICES", "BLOCK_SIZE_SCATTER_CHECK_INDICES", "SHARED_MEM_SIZE_SCATTER_CHECK_INDICES"}},
    {"scatter_nd", {"GRID_SIZE_SCATTER_ND", "BLOCK_SIZE_SCATTER_ND", "SHARED_MEM_SIZE_SCATTER_ND"}},
    {"scatter_simple", {"GRID_SIZE_SCATTER_SIMPLE", "BLOCK_SIZE_SCATTER_SIMPLE", "SHARED_MEM_SIZE_SCATTER_SIMPLE"}},
    {"scatter_update", {"GRID_SIZE_SCATTER_UPDATE", "BLOCK_SIZE_SCATTER_UPDATE", "SHARED_MEM_SIZE_SCATTER_UPDATE"}},
    {"segment_indices", {"GRID_SIZE_SEGMENT_INDICES_VALIDATE", "BLOCK_SIZE_SEGMENT_INDICES_VALIDATE", "SHARED_MEM_SIZE_SEGMENT_INDICES_VALIDATE"}},
    {"segment", {"GRID_SIZE_SEGMENT", "BLOCK_SIZE_SEGMENT", "SHARED_MEM_SIZE_SEGMENT"}},
    {"segment_tad", {"GRID_SIZE_SEGMENT_TAD", "BLOCK_SIZE_SEGMENT_TAD", "SHARED_MEM_SIZE_SEGMENT_TAD"}},
    {"segment_prod_2", {"GRID_SIZE_SEGMENT_PROD_2_LINEAR", "BLOCK_SIZE_SEGMENT_PROD_2_LINEAR", "SHARED_MEM_SIZE_SEGMENT_PROD_2_LINEAR"}},
    {"segment_prod_2_tad", {"GRID_SIZE_SEGMENT_PROD_2_TAD", "BLOCK_SIZE_SEGMENT_PROD_2_TAD", "SHARED_MEM_SIZE_SEGMENT_PROD_2_TAD"}},
    {"unsorted_segment_prod_2", {"GRID_SIZE_UNSORTEDSEGMENT_PROD_2", "BLOCK_SIZE_UNSORTEDSEGMENT_PROD_2", "SHARED_MEM_SIZE_UNSORTEDSEGMENT_PROD_2"}},
    {"solve", {"GRID_SIZE_SOLVE", "BLOCK_SIZE_SOLVE", "SHARED_MEM_SIZE_SOLVE"}},
    {"sru_bi", {"GRID_SIZE_SRU_BI", "BLOCK_SIZE_SRU_BI", "SHARED_MEM_SIZE_SRU_BI"}},

};


// Retrieve the environment variable value for the given variable name
int getEnvVariable(const std::string& varName, int defaultValue) {
  const char* envValue = std::getenv(varName.c_str());
  if (envValue != nullptr) {
    return std::atoi(envValue);
  }
  return defaultValue;
}




dim3 getLaunchDims(const std::string& key) {
  // Look for the key in the cache
  // Key not found in the cache
  // Check if there is an environment variable with this key
  auto algoValue = algoDimMapString[key.c_str()];
  dim3 returnValue;
  dim3 defaultValue = algoDimMap[key.c_str()];
  auto xKey = algoValue[0].c_str();
  auto yKey = algoValue[1].c_str();
  auto zKey = algoValue[2].c_str();
  char* envValueX = std::getenv(xKey);
  char* envValueY = std::getenv(yKey);
  char* envValueZ = std::getenv(zKey);

  //Set the return values
  //dynamically overriding whatever was compiled
  //with the environment variables if found
  if(envValueX) {
    sd_printf("Overriding %s with %s\n", xKey, envValueX);
    returnValue.x = std::atoi(envValueX);
  } else {
    sd_printf("Using default value x %d with key lookup %s\n", defaultValue.x, xKey);
    returnValue.x = defaultValue.x;
  }

  if(envValueY) {
    sd_printf("Overriding %s with %s\n", yKey, envValueY);
    returnValue.y = std::atoi(envValueY);
  } else {
    sd_printf("Using default value y %d with key lookup %s\n", defaultValue.y, yKey);
    returnValue.y = defaultValue.y;
  }

  if(envValueZ) {
    sd_printf("Overriding %s with %s\n", xKey, envValueX);
    returnValue.z = std::atoi(envValueZ);
  } else {
    sd_printf("Using default value z %d with key lookup %s\n", defaultValue.z, zKey);
    returnValue.z = defaultValue.z;
  }

  // Return the result
  return returnValue;
}



dim3 getMMulDims(int length,int sizeofDataType) {
  dim3 threadsPerBlock(512);
  dim3 blocksPerGrid(1);
  if (length > 512) threadsPerBlock.x = sd::math::sd_ceil<double, int>(static_cast<double>(length) / 512);
  return  dim3(512, threadsPerBlock.x,  length * sizeofDataType + 128);
}

dim3 getAccumDims(int xLength) {
  dim3 launchDims = getLaunchDims("accumulate");
  dim3 launchDims2(xLength, launchDims.y, launchDims.z);
  return launchDims2;
}

dim3 getReduceDims(int xLength) {
  auto blockWidth = 256;
  auto numBlocks = sd::CudaLaunchHelper::getReductionBlocks(xLength, blockWidth);
  dim3 launchDims(numBlocks == 0 ? 1 : numBlocks, blockWidth, 8192);
  return launchDims;;
}

dim3 getSortFullDims(int xLength) {
  int numThreads = sd::math::sd_min<int>(512, xLength);
  int numBlocks = xLength / numThreads;
  if (xLength % numThreads > 0 || numBlocks == 0) numBlocks++;

  numBlocks = sd::math::sd_min<int>(512, numBlocks);
  dim3 launchDims(numBlocks, numThreads, 32768);
  return launchDims;
}

dim3 getSortTadLarge(int numberTads) {
  return dim3(numberTads, 512,33768);
}
dim3 getSortTadDims(int numberTads) {
  return dim3(numberTads, 256,2048);
}

dim3 getFillUpSegmentsDims(int numClasses,int length) {
  return dim3(numClasses, length, numClasses * 32 + 32);
}

dim3 getSegmentSumDims(int numClasses,int length) {
  return dim3(numClasses, length, (numClasses + 1)  * 64);
}


dim3 getSequenceMaskLaunchDims(int maxIndex,sd::NDArray input) {
  int maxThreads = maxIndex;
  int maxBlocks = input.lengthOf();
  int sharedMem = 128;
  return dim3(maxBlocks, maxThreads, sharedMem);
}

dim3 getCol2imLaunchParams(sd::NDArray im,sd::NDArray col) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (im.lengthOf() + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = col.rankOf() * sizeof(sd::LongType) * threadsPerBlock + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_COL2IM", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_COL2IM", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_COL2IM", sharedMem);
  sd_printf("Col2IM: threadsPerBlock: %i, blocksPerGrid: %i, sharedMem: %i\n", threadsPerBlock, blocksPerGrid, sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}

dim3 getim2ColLaunchParams(sd::NDArray col) {
  int threadsPerBlock = 512;
  int blocksPerGrid = (col.lengthOf() + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = col.rankOf() * sizeof(sd::LongType) * threadsPerBlock + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_IM2COL", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_IM2COL", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_IM2COL", sharedMem);
  sd_printf("IM2COL: threadsPerBlock: %i, blocksPerGrid: %i, sharedMem: %i\n", threadsPerBlock, blocksPerGrid, sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}


dim3 getGemVDims(int m) {
  int threadsPerBlock = SD_MAX_NUM_THREADS;
  int blocksPerGrid = (m + threadsPerBlock - 1) / threadsPerBlock;

  threadsPerBlock = getEnvVariable("GRID_SIZE_GEMV", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_GEMV", blocksPerGrid);
  //sharedMem isn't used
  return dim3(blocksPerGrid, threadsPerBlock, 0);
}

dim3 getAddBiasDims(int len,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (len + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = rank * sizeof(sd::LongType) * threadsPerBlock + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_ADDBIAS", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_ADDBIAS", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_ADDBIAS", sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}


dim3 getPoolingDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = rank * sizeof(sd::LongType) * threadsPerBlock + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_POOLING", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_POOLING", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_POOLING", sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}

dim3 getCol2VolDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = rank * sizeof(sd::LongType) * threadsPerBlock + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_COL2VOL", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_COL2VOL", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_COL2VOL", sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}

dim3 getVol2ColDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = rank * sizeof(sd::LongType) * threadsPerBlock + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_VOL2COL", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_VOL2COL", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_VOL2COL", sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}

dim3 getUpsamplingDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = rank * sizeof(sd::LongType) * threadsPerBlock + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_UPSAMPLING", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_UPSAMPLING", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_UPSAMPLING", sharedMem);
  return dim3(blocksPerGrid, threadsPerBlock, sharedMem);
}

dim3 getHistogramDims(int length,int numBins) {
  int threadsPerBlock = 256;
  int blocksPerGrid = sd::math::sd_max<int>(256, sd::math::sd_min<int>(1, length / threadsPerBlock));
  int workspaceSize = blocksPerGrid * numBins;
  threadsPerBlock = getEnvVariable("GRID_SIZE_HISTOGRAM", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_HISTOGRAM", blocksPerGrid);
  workspaceSize = getEnvVariable("SHARED_MEM_SIZE_HISTOGRAM", workspaceSize);
  return dim3(blocksPerGrid, threadsPerBlock, workspaceSize);
}

dim3 getAdjustDims(int numTads) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (numTads + threadsPerBlock - 1) / threadsPerBlock;
  threadsPerBlock = getEnvVariable("GRID_SIZE_ADJUST", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_ADJUST", blocksPerGrid);
  //shared memory isn't used
  return dim3(blocksPerGrid, threadsPerBlock, 0);
}

dim3 getBatchNormDims(int length) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  threadsPerBlock = getEnvVariable("GRID_SIZE_BATCHNORM", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_BATCHNORM", blocksPerGrid);
  return dim3(threadsPerBlock,blocksPerGrid,0);


}

dim3 getCompareAndBitpackDims(int length) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  threadsPerBlock = getEnvVariable("GRID_SIZE_COMPARE_AND_BITPACK", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_COMPARE_AND_BITPACK", blocksPerGrid);
  return dim3(threadsPerBlock,blocksPerGrid,0);


}

dim3 getCompareElem(int length) {
  int threadsPerBlock = 256;
  int numBlocks = sd::math::sd_min<int>(128, sd::math::sd_max<int>(1, length / threadsPerBlock));
  int sharedMemory = threadsPerBlock * 4 + 1024;
  threadsPerBlock = getEnvVariable("GRID_SIZE_COMPARE_AND_BITPACK", threadsPerBlock);
  numBlocks = getEnvVariable("BLOCK_SIZE_COMPARE_AND_BITPACK", numBlocks);
  sharedMemory = getEnvVariable("SHARED_MEM_SIZE_COMPARE_AND_BITPACK", sharedMemory);
  return dim3(threadsPerBlock,numBlocks,sharedMemory);


}

dim3 getConcat(int length) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = 256;

  threadsPerBlock = getEnvVariable("GRID_SIZE_CONCAT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_CONCAT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_CONCAT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 getBetaInc(int maxIter,int length,int dataTypeSize) {
  int threadsPerBlock = maxIter;
  int blocksPerGrid = length;
  int sharedMem = 2 * dataTypeSize * threadsPerBlock + 128;


  threadsPerBlock = getEnvVariable("GRID_SIZE_CONCAT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_CONCAT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_CONCAT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 getCross(int length,int rank,int lastSize) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length / lastSize + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = sizeof(sd::LongType) * threadsPerBlock * rank + 128;

  threadsPerBlock = getEnvVariable("GRID_SIZE_CONCAT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_CONCAT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_CONCAT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}


dim3 getDilation(int outputLength,int weightRank,int outputRank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (outputLength + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = (weightRank + outputRank) * sizeof(sd::LongType) * threadsPerBlock + 128;

  threadsPerBlock = getEnvVariable("GRID_SIZE_CONCAT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_CONCAT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_CONCAT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 getGatherLinear(int numSubArrs) {
  int numBlocks = numSubArrs;
  int threadsPerBlock = SD_MAX_NUM_THREADS;
  int sharedMem = 1024;
  threadsPerBlock = getEnvVariable("GRID_SIZE_GATHER", threadsPerBlock);
  numBlocks = getEnvVariable("BLOCK_SIZE_GATHER", numBlocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_GATHER", sharedMem);
  return dim3(threadsPerBlock,numBlocks,sharedMem);
}

dim3 getGatherNd(int outputLength,int maxRank) {
  int threadsPerBlock = 256;
  int blocksPerGrid = (outputLength + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = 8 * threadsPerBlock * maxRank + 128;

  threadsPerBlock = getEnvVariable("GRID_SIZE_GATHER", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_GATHER", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_GATHER", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 getHashCodeSplit(int length,int blockSize) {
  int threadsPerBlock = 1;
  int blocksPerGrid = length / blockSize + ((length % blockSize == 0) ? 0 : 1);
  int sharedMem = 1024;

  threadsPerBlock = getEnvVariable("GRID_SIZE_HASHCODE_SPLIT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_HASHCODE_SPLIT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_HASHCODE_SPLIT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 getHashCodeInternal(int numBlocks) {
  int threadsPerBlock = 1;
  int blocksPerGrid = numBlocks;
  int sharedMem = 1024;

  threadsPerBlock = getEnvVariable("GRID_SIZE_HASHCODE_INTERNAL", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_HASHCODE_INTERNAL", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_HASHCODE_INTERNAL", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 cropAndResize(int batchSize,int imageHeight,int imageWidth,int cropHeight,int cropWidth) {
  int threadsPerBlock = sd::math::sd_max(imageHeight * imageWidth, cropHeight * cropWidth);
  if (threadsPerBlock > SD_MAX_NUM_THREADS / 4) threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = batchSize;
  int sharedMem = 256;

  threadsPerBlock = getEnvVariable("GRID_SIZE_CROP_AND_RESIZE", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_CROP_AND_RESIZE", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_CROP_AND_RESIZE", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);


}

dim3 imageHelper(int numTads) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (numTads + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMemory = 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_IMAGE_HELPERS", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_GRID_SIZE_IMAGE_HELPERS", blocksPerGrid);
  sharedMemory = getEnvVariable("SHARED_MEM_SIZE_GRID_SIZE_IMAGE_HELPERS", sharedMemory);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMemory);
}

dim3 lrnDims(int tadLength,int numTads, int xDTypeSize,int zDTypeSize) {
  int numBlocks = sd::math::sd_min<sd::LongType>(1024, numTads);
  int numThreads = tadLength;
  int sharedMem = numThreads * xDTypeSize + numThreads * zDTypeSize + 1024;
  numThreads = getEnvVariable("GRID_SIZE_LRN", numThreads);
  numBlocks = getEnvVariable("BLOCK_SIZE_LRN", numBlocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_LRN", sharedMem);
  return dim3(numThreads,numBlocks,sharedMem);

}

dim3 lupDims(int n) {
  int blockSize = 1;
  int numThreads = n;
  int sharedMem = 512;
  numThreads = getEnvVariable("GRID_SIZE_LUP", numThreads);
  blockSize = getEnvVariable("BLOCK_SIZE_LUP", blockSize);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_LUP", sharedMem);

  return dim3(numThreads,blockSize,sharedMem);
}

dim3 lupDimsLow(int n) {
  int blockSize = n;
  int numThreads = n;
  int sharedMem = 512;
  numThreads = getEnvVariable("GRID_SIZE_LUP_LOW", numThreads);
  blockSize = getEnvVariable("BLOCK_SIZE_LUP_LOW", blockSize);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_LUP_LOW", sharedMem);

  return dim3(numThreads,blockSize,sharedMem);
}

dim3 matrixSetDiagDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_MATRIX_SET_DIAG", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_MATRIX_SET_DIAG", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_MATRIX_SET_DIAG", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 mergeDims(int length) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = 512;
  threadsPerBlock = getEnvVariable("GRID_SIZE_MERGE", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_MERGE", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_MERGE", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}


dim3 oneHotDims(int length,int rank,int shapeSize) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * shapeSize * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_ONE_HOT", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_ONE_HOT", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_ONE_HOT", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 padDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = 8 * threadsPerBlock * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_PAD", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_PAD", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_PAD", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 polygammaDims(int length) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = 1024;
  threadsPerBlock = getEnvVariable("GRID_SIZE_POLYGAMMA", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_POLYGAMMA", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_POLYGAMMA", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 prefixDims(int numTads,int sizeOfDataType) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = numTads;
  int sharedMem = 2 * threadsPerBlock * sizeOfDataType + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_PREFIX", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_PREFIX", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_PREFIX", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 randomShuffleFisherDims(int power,int inputDataTypeSize) {
  int blocksPerGrid = 1 << power;
  int threadsPerBlock = SD_MAX_NUM_THREADS;
  int sharedMem = threadsPerBlock * inputDataTypeSize + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_RANDOM_SHUFFLE_FISHER", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_RANDOM_SHUFFLE_FISHER", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_RANDOM_SHUFFLE_FISHER", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 batchToSpaceNdLaunch(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_BATCH_TO_SPACE_ND", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_BATCH_TO_SPACE_ND", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_BATCH_TO_SPACE_ND", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 spaceToBatchLaunch(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_SPACE_TO_BATCH", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SPACE_TO_BATCH", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SPACE_TO_BATCH", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 spaceToBatchNdLaunch(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_SPACE_TO_BATCH", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SPACE_TO_BATCH", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SPACE_TO_BATCH", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}

dim3 scatterDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = ((length) + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = sizeof(sd::LongType) * threadsPerBlock * (rank) + 256;
  threadsPerBlock = getEnvVariable("GRID_SIZE_SCATTER", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SCATTER", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SCATTER", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 scatterDimsCheckIndices(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 2;
  int blocksPerGrid = (length + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 256;

  threadsPerBlock = getEnvVariable("GRID_SIZE_SCATTER_CHECK_INDICES", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SCATTER_CHECK_INDICES", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SCATTER_CHECK_INDICES", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}

dim3 scatterNdDims(int length,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = ((length) + threadsPerBlock - 1) / threadsPerBlock;
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) * rank + 512;
  threadsPerBlock = getEnvVariable("GRID_SIZE_SCATTER_ND", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SCATTER_ND", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SCATTER_ND", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}


dim3 segmentValidateIndices(int length) {
  int threadsPerBlock = 1;
  int blocksPerGrid = length;
  int sharedMem = 128;
  threadsPerBlock = getEnvVariable("GRID_SIZE_SEGMENT_INDICES_VALIDATE", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SEGMENT_INDICES_VALIDATE", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SEGMENT_INDICES_VALIDATE", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);
}


dim3 segmentDims(int numClasses,int length) {
  int blocks  = numClasses;
  int threads = length;
  int sharedMem = numClasses * 32 + 32;
  threads = getEnvVariable("GRID_SIZE_SEGMENT", threads);
  blocks = getEnvVariable("BLOCK_SIZE_SEGMENT", blocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SEGMENT", sharedMem);
  return dim3(threads,blocks,sharedMem);

}

dim3 segmentTad(int size) {
  int blocks = size;
  int threads = 512;
  int sharedMem = 2048;
  threads = getEnvVariable("GRID_SIZE_SEGMENT_TAD", threads);
  blocks = getEnvVariable("BLOCK_SIZE_SEGMENT_TAD", blocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SEGMENT_TAD", sharedMem);
  return dim3(threads,blocks,sharedMem);
}

dim3 segmentBpDims(int gradOutLen,int inputLen) {
  int threads = gradOutLen;
  int blocks = inputLen;
  int sharedMem = 256;
  threads = getEnvVariable("GRID_SIZE_SEGMENT_BP", threads);
  blocks = getEnvVariable("BLOCK_SIZE_SEGMENT_BP", blocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SEGMENT_BP", sharedMem);
  return dim3(threads,blocks,sharedMem);
}

dim3 segmentBpTad(int indicesLen,int inputLen) {
  int threads = indicesLen;
  int blocks = inputLen;
  int sharedMem = 256;
  threads = getEnvVariable("GRID_SIZE_SEGMENT_BP_TAD", threads);
  blocks = getEnvVariable("BLOCK_SIZE_SEGMENT_BP_TAD", blocks);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SEGMENT_BP_TAD", sharedMem);
  return dim3(threads,blocks,sharedMem);

}

dim3 sruBiDims(int len,int rank) {
  int threadsPerBlock = SD_MAX_NUM_THREADS / 4;
  int blocksPerGrid = len + threadsPerBlock - 1 /
                                              threadsPerBlock;  // loop through last two dimensions of x array -> bS, 2*K
  int sharedMem = threadsPerBlock * sizeof(sd::LongType) *rank + 128;

  threadsPerBlock = getEnvVariable("GRID_SIZE_SRU_BI", threadsPerBlock);
  blocksPerGrid = getEnvVariable("BLOCK_SIZE_SRU_BI", blocksPerGrid);
  sharedMem = getEnvVariable("SHARED_MEM_SIZE_SRU_BI", sharedMem);
  return dim3(threadsPerBlock,blocksPerGrid,sharedMem);

}
#endif //LIBND4J_LAUNCHCONTEXT_H