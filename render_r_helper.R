library(xml2)
library(stringr)

#' \code{extract_short_flags} extract short flag letters from XML file.
#'
#' @param xml_file_name XML file name in the galaxy tool repository directory in GTG
#' @param gtg_name The name of a running GTG.
extract_short_flags = function(xml_file_name, gtg_name = 'gtg') {
    gtg_directory = get_gtg_directory(gtg_name)
    xml_file_con = file(paste0(gtg_directory, 'galaxy_tool_repository/', xml_file_name))
    xml = read_xml(xml_file_con)
    command_text = xml_text(xml_find_all(xml, './/command'))
    short_flags = str_match_all(command_text, "\\-[A-Za-z1-9]")[[1]][,1]
    if(length(short_flags) < 1)
    cat('No short flags found in ', xml_file_name, '\n')
    short_flags = str_replace(short_flags, '-', '')
    short_flags
}

#' \code{getopt_specification_matrix} creates a getopt specification matrix and add it to an existing getopt spcification matrix
#'
#' @param short_flags a vector of short flags, for example, \code{c('a', 'b', 'k', 'h')}
#' @argument_mask_flag an integer indicating the argumen types. Possible values: 0 = 'the corresponding flag do not need argument',
#' 1 = 'the corresponding flag require argument', 2 = 'argument is optional for the corresponding flag.'
#' @param spec_matrix an getopt specification matrix returned from the \code{getopt_specification_matrix} function.
getopt_specification_matrix = function(short_flags, argument_mask_flag = 'character', spec_matrix = matrix(nrow = 0, ncol = 4)) {
    long_flags = paste0('X_', short_flags)
    argument_mask_flags = rep(1, length(short_flags))
    data_type_flags = rep(argument_mask_flag, length(short_flags))
    temp_matrix = cbind(long_flags, short_flags, argument_mask_flags, data_type_flags)
    res = rbind(spec_matrix, temp_matrix)
    if(length(unique(res[, 'short_flags'])) != nrow(res))
    stop('Short flags need to be unique!')
    if(length(unique(res[, 'long_flags'])) != nrow(res))
    stop('Long flags need to be unique!')
    res
}



