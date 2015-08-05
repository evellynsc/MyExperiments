#usage: Rscript ga_evolution.R <folder-name> <dataset-id> <id-of-xp> <number-of-xp>


args = commandArgs(TRUE)

folder_name = args[1]
dataset_id = args[2]
id_xp = args[3]
n_xp = args[4]

# print(folder_name)
# print(dataset_id)

my.panel.bands <- function(x, y, upper, lower, fill, col, subscripts, ..., font, fontface){
	upper <- upper[subscripts]
	lower <- lower[subscripts]
	panel.polygon(c(x, rev(x)), c(upper, rev(lower)), col = fill, border = FALSE, ...)
}

calculate.98.confidence.error <- function(data) {
	error = qt(0.99, df=length(data)-1)*sd(data)/sqrt(length(data))
	return(error)
}

confidence.interval.evolution <- function(data_list, n_ger) {
	data = matrix(0,nrow=n_ger,ncol=length(data_list))
	for(i in 1:length(data_list)) {
		data[,i] = data_list[[i]][1:n_ger]
	}
	average = apply(data, 1, mean)
	error = apply(data, 1, calculate.98.confidence.error)
	low = average - error
	up = average + error

	interval = matrix(0, nrow=n_ger, ncol=3)
	interval[,1] = average*100
	interval[,2] = low*100
	interval[,3] = up*100

	# y_max = max(c(left, right, average)) + max(c(left, right, average))/4
	# y_min = min(c(left, right, average)) - min(c(left, right, average))/4

	# # postscript(paste(file_name, ".eps", sep=''))
	# plot(average, type='l', col='red', ylim=c(y_min,y_max))
	# lines(left, col='gray')
	# lines(right, col='gray')
	# dev.off()
	return(interval)
}

setwd(folder_name)
# select all files that match the dataset id
all_dataset_files = dir()[which(substr(x=dir(), start=2, stop=2) == dataset_id)]
# select all csv files
all_csv_files = grep(pattern='.csv', x=all_dataset_files, value=T)
all_data = 0

for(i in 1:n_xp) {
	xp_files = grep(pattern=paste("exp", i, sep=""), x=all_csv_files, value=T)
	
	fitness = list()
	n_ger = c()
	count = 1

	for(f in xp_files) {
		data_xp = read.table(f, sep=';', header=T)
		n_ger = c(n_ger, dim(data_xp)[1])
		fitness[[count]] = data_xp$fitness
		count = count + 1
	}
	n_ger = min(n_ger)
	result = confidence.interval.evolution(fitness, n_ger)
	result = cbind(result, c(1:n_ger), rep(i,n_ger))

	if(is.matrix(all_data) == 0) {
		all_data = result
	} else {
		all_data = rbind(all_data, result)
	}
}

all_data = as.data.frame(all_data)
colnames(all_data) = c("fitness", "low", "high", "generation", "experiment")

# print(dim(all_data))
# print(all_data)

library(lattice)
lattice.options(default.theme=standard.theme(color=FALSE))
# all_plot <- xyplot(fitness ~ generation | experiment, data = all_data, type = 'l')
# print(all_plot)

all_data$experiment = as.factor(all_data$experiment)
all_plot <- xyplot(fitness ~ generation | experiment, data=all_data, groups=experiment, 
	upper = all_data$high, lower = all_data$low, 
	index.cond=list(c(6,7,8,3,4,5,1,2)),
	panel = function(x, y, ...){
		panel.superpose(x, y, panel.groups = my.panel.bands, type='l', fill='gray', col='gray',...)
 		panel.xyplot(x, y, type='l', cex=0.6, lty=1,...)
 	}
)


plot_name = paste("E",dataset_id,"-XP",id_xp,".pdf", sep="")
trellis.device(pdf, file=plot_name)
print(all_plot)
dev.off()