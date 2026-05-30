.PHONY: close show-testcase random-test my-test-command

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

close: 
	@if [ -f ./random_input.txt ]; then \
		rm ./random_input.txt; \
	fi

	@if [ -f ./target_output.txt ]; then \
		rm ./target_output.txt; \
	fi

	@if [ -f ./naive_output.txt ]; then \
		rm ./naive_output.txt; \
	fi

	@if [ -f ./target.out ]; then \
		rm ./target.out; \
	fi

	@if [ -f ./naive.out ]; then \
		rm ./naive.out; \
	fi


show-testcase: 
	@echo "-------Input-------"; \
	cat ./random_input.txt; \
	echo "-------------------"; \
	echo "---Target-Output---"; \
	cat ./target_output.txt; \
	echo "-------------------"; \
	echo "---Naive--Output---"; \
	cat ./naive_output.txt; \
	echo "-------------------";

random-test: 
#	RANDOM_TESTCASE_GEN_FILE_PATH の引数がセットされているか判定
	@if [ -z "$${RANDOM_TESTCASE_GEN_FILE_PATH}" ]; then \
		echo "RANDOM_TESTCASE_GEN_FILE_PATH is not set"; \
		exit 1; \
	fi; 

#	NAIVE_ALGO_FILE_PATH の引数がセットされているか判定
	@if [ -z "$${NAIVE_ALGO_FILE_PATH}" ]; then \
		echo "NAIVE_ALGO_FILE_PATH is not set"; \
		exit 1; \
	fi; 

#	TARGET_ALGO_FILE_PATH の引数がセットされているか判定
	@if [ -z "$${TARGET_ALGO_FILE_PATH}" ]; then \
		echo "TARGET_ALGO_FILE_PATH is not set"; \
		exit 1; \
	fi; 

#	RANDOM_TESTCASE_GEN_FILE_PATH の引数がセットされているか判定
	@if [ ! -f "$${RANDOM_TESTCASE_GEN_FILE_PATH}" ]; then \
		echo "RANDOM_TESTCASE_GEN_FILE_PATH doesn't exist"; \
		exit 1; \
	fi; 

#	NAIVE_ALGO_FILE_PATH の引数がセットされているか判定
	@if [ ! -f "$${NAIVE_ALGO_FILE_PATH}" ]; then \
		echo "NAIVE_ALGO_FILE_PATH doesn't exist"; \
		exit 1; \
	fi; 

#	TARGET_ALGO_FILE_PATH の引数がセットされているか判定
	@if [ ! -f "$${TARGET_ALGO_FILE_PATH}" ]; then \
		echo "TARGET_ALGO_FILE_PATH doesn't exist"; \
		exit 1; \
	fi;

#   TRY_COUNT 回だけテストを開始
#	 RANDOM_TESTCASE_GEN_FILE_PATH が "cpp" であるか，"py"であるかで場合分け
	@g++ "$${TARGET_ALGO_FILE_PATH}" -o target.out; \
	g++ "$${NAIVE_ALGO_FILE_PATH}" -o naive.out; \
	\
	case "$${RANDOM_TESTCASE_GEN_FILE_PATH}" in \
		*.cpp) \
			g++ "$${RANDOM_TESTCASE_GEN_FILE_PATH}" -o ./testcase.out; \
			for _ in $$(seq 1 "$${TRY_COUNT}"); do \
				./testcase.out > ./random_input.txt; \
				\
				./target.out < ./random_input.txt > ./target_output.txt; \
				./naive.out < ./random_input.txt > ./naive_output.txt; \
				\
				if ! diff ./target_output.txt ./naive_output.txt > /dev/null 2>&1; then \
					echo 'Output [ Unmatched ]'; \
					cp ./random_input.txt ./unmatched_input.txt; \
					$(MAKE) show-testcase -f "$(MAKEFILE_PATH)"; \
					$(MAKE) close -f "$(MAKEFILE_PATH)"; \
					exit 0; \
				fi; \
				echo 'Output [ Matched ]'; \
			done; \
			;; \
		*.py) \
			for _ in $$(seq 1 "$${TRY_COUNT}"); do \
				python "$${RANDOM_TESTCASE_GEN_FILE_PATH}" > ./random_input.txt; \
				\
				./target.out < ./random_input.txt > ./target_output.txt; \
				./naive.out < ./random_input.txt > ./naive_output.txt; \
				\
				if ! diff ./target_output.txt ./naive_output.txt > /dev/null 2>&1 ; then \
					echo 'Output [ Unmatched ]'; \
					cp ./random_input.txt ./unmatched_input.txt; \
					$(MAKE) show-testcase -f "$(MAKEFILE_PATH)"; \
					$(MAKE) close -f "$(MAKEFILE_PATH)"; \
					exit 0; \
				fi; \
				echo 'Output [ Matched ]'; \
			done; \
			;; \
	esac; \
	$(MAKE) close -f "$(MAKEFILE_PATH)"; \

my-test-command: 
	@$(MAKE) random-test RANDOM_TESTCASE_GEN_FILE_PATH="./ABC459_E_generate.cpp" \
						 NAIVE_ALGO_FILE_PATH="./ABC459_E_naive.cpp" \
						 TARGET_ALGO_FILE_PATH="./ABC459_E.cpp" \
						 TRY_COUNT=100 \
						 -f "$(MAKEFILE_PATH)"
